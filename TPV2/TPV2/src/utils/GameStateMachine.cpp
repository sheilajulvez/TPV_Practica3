#include "GameStateMachine.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"
#include "../states/GameOverState.h"
#include "../states/WinState.h"
#include "../sdlutils/SDLUtils.h"
#include "../states/MainMenuState.h"


GameStateMachine::GameStateMachine() {
	
	

}
GameStateMachine::~GameStateMachine() {
	while (!gamestate_stack.empty()) {
		auto c = gamestate_stack.top();
		delete(c);
		gamestate_stack.pop();
	}
	for (auto e = gamestate_list.begin(); e != gamestate_list.end();) {
		auto c = e;
		++e;
		delete(*c);
		gamestate_list.remove(*c);
	}
}

 void GameStateMachine::init() {
	/*pushState(new PlayState(this));
	pushState(new PauseState(this));*/
	 pushState(new MainMenuState(this));
}

Manager* GameStateMachine::currentState() const {
	return gamestate_stack.top();
}

void GameStateMachine::pushState(Manager* state) {
	gamestate_stack.push(state);
}

void GameStateMachine::changeState(Manager * state) {
	popState();
	pushState(state);	
}
void GameStateMachine::popState() {
	gamestate_list.push_back(currentState());
	gamestate_stack.pop();
	if (!gamestate_stack.empty()&&typeid(*gamestate_stack.top()) == typeid(PlayState)) {
		static_cast<PlayState*>(gamestate_stack.top())->Reset();
	}
}
void GameStateMachine::empty_stack() {
	while (!gamestate_stack.empty()) {
		popState();
	}
}
void GameStateMachine::for_list() {
	
	for (auto e = gamestate_list.begin(); e != gamestate_list.end();) {
		auto c = e; 
		++e;
		delete(*c);
		gamestate_list.remove(*c);
	}
}

void GameStateMachine::Exit_true() {
	exit = true;
	Game::instance()->exit_();
}

void GameStateMachine::run()
{
	// pintamos todas las veces que pueda y solo actualizamos cuando queremos, no paralizamos el proyecto
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();				//cuanto tiempo llevamos
	//bucle principal
	while (!exit) {
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= 5) {
			update();
			startTime = SDL_GetTicks(); //resetea el contador y vuelve a empezar desde 0
			// se actualiza desde el ultimo update hecho
			for_list();
		}
		render();

	}
	
	//si pierdes, carga imagen de Game Over
	
	//cuando te sales
	//else if (exit) cout << "Has pulsado cerrar , x superior derecha";
}
void GameStateMachine::render() {
	SDL_RenderClear(SDLUtils::instance()->renderer());
	//if(!gamestate_stack.empty())gamestate_stack.top()->render();
	SDL_RenderPresent(SDLUtils::instance()->renderer());
}
void GameStateMachine::update() {
	
	if (!gamestate_stack.empty()) { gamestate_stack.top()->update(); gamestate_stack.top()->refresh(); }
}
void GameStateMachine::handleEvents() {
	if (!gamestate_stack.empty())gamestate_stack.top()->handleEvents();
}