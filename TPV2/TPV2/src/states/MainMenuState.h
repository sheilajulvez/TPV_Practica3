#pragma once
#include "../ecs/Manager.h"
#include "../utils/GameStateMachine.h"
#include "../sdlutils/Font.h"
#include "../sdlutils/SDLUtils.h"
class MainMenuState:public Manager
{
private:
	GameStateMachine* g;
	Font* f = &SDLUtils::instance()->fonts().at("ARIAL16");
public:
	MainMenuState(GameStateMachine* g);
	virtual ~MainMenuState();
	void update();



};

