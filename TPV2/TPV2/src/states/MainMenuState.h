#pragma once
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Font.h"
#include "../game/Constantes.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/GameStateMachine.h"

class MainMenuState: public Manager
{
protected:
	Font* f= &SDLUtils::instance()->fonts().at("ARIAL16");
	SDL_Color c = { 255,255,0 };
	GameStateMachine* g;
public:
	MainMenuState(GameStateMachine* gs);
	~MainMenuState();
	void update();

};

