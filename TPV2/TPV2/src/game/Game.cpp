#include "Game.h"

#include "../utils/GameStateMachine.h"

//#include "states/TopDownState.h"

Game::Game(char* host, int port) {
	SDLUtils::init("Oscar Te AMOO!",WIN_WIDTH,WIN_HEIGHT,
		"resources/config/sdlutilsdemo.resources.json");
	//instance();
	renderer = SDLUtils::instance()->renderer();
	window = SDLUtils::instance()->window();
	exit = false;
	gameStMc = GameStateMachine::instance();
	calcetin =  SDLNet_UDP_Open(0);

	if (SDLNet_ResolveHost(&srvadd, host, port) < 0) {
		throw("ERROR AL ESTABLECER CONEXION CON EL SERVIDOR");
		//error(); 
	}
	p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	gameStMc->init();
	
}

Game::~Game()// destructora
{
	delete(gameStMc);// destruye game State Machine
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Game::free_() {
	delete(gameStMc);// destruye game State Machine
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Game::run()// bucle de juego
{
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	
	while (!exit) // bucle de juego
	{
		//SDL_RenderClear(renderer);

		//handleEvents();
		cout << "Enter a message: ";
		cin.getline(buffer, 255);
		if (strcmp(buffer, "exit") == 0) { break; }
		p->len = static_cast<int>(strlen(buffer)) + 1;
		p->address = srvadd;
		SDLNet_UDP_Send(sd, -1, p);
		if (SDLNet_CheckSockets(socketSet, 3000) > 0) {
			if (SDLNet_SocketReady(sd)) {
				while (SDLNet_UDP_Recv(sd, p) > 0) {
					cout << "Server says: " << buffer << endl;
				}
			}
		}

		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE)
		{
			update();
			
			//gameStMc->clearStates(); // elimina estados
			startTime = SDL_GetTicks();
		}
		if (!exit)
		{
			//SDL_RenderClear(renderer);
			//render();
			//SDL_RenderPresent(renderer);// dibuja en pantalla el estado actual del juego
			//SDL_Delay(10);
		}
	}
}

void Game::handleEvents() {
	// handleEvents
	gameStMc->handleEvents();
}

void Game::update()
{
	//update
	gameStMc->update();// actualiza el juego
	gameStMc->for_list();
	

}

void Game::render() {
	//render
	gameStMc->render();
}