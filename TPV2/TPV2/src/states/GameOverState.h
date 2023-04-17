#pragma once
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Font.h"
#include "../game/ecs_defs.h"
#include "../utils/checkML.h"
#include "../systems/renderSystem.h"
#include "../systems/FighterSystem.h"
class GameStateMachine;
class GameOverState: public Manager
{
private:
	GameStateMachine* gsm;
	Font* f;
	RenderSystem* render;
	FighterSystem* fighter;
public:
	GameOverState(GameStateMachine* gsm);
	virtual ~GameOverState() {

	}
	//void render();
	void handleEvents();
};

