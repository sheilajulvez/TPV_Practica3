#include "Game.h"

#include "../utils/GameStateMachine.h"

//#include "states/TopDownState.h"

Game::Game() {
	SDLUtils::init("Oscar Te AMOO!",WIN_WIDTH,WIN_HEIGHT,
		"resources/config/sdlutilsdemo.resources.json");
	//instance();
	renderer = SDLUtils::instance()->renderer();
	window = SDLUtils::instance()->window();
	exit = false;
	gameStMc = GameStateMachine::instance();
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