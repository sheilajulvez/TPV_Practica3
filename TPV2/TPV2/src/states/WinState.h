#pragma once
#include "../ecs/Manager.h"
#include "../sdlutils/Font.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/ecs_defs.h"
#include "../utils/checkML.h"
#include "../systems/RenderSystem.h"
#include "../systems/FighterSystem.h"
class GameStateMachine;
class WinState: public Manager
{
protected:
	GameStateMachine* gsm;
	Font* f;
	RenderSystem* render;
	FighterSystem* fighter;

public:
	WinState(GameStateMachine* gs) {
		gsm = gs;
		f = &SDLUtils::instance()->fonts().at("ARIAL16");

		render=addSystem<RenderSystem>(2);
		render->setContext(this);
		gamecontrolsystem->setContext(this);
		gamecontrolsystem->setstate_(2);
		fighter = addSystem<FighterSystem>();

	}
	virtual ~WinState() {

	}
	//void render();
	void handleEvents();

};

