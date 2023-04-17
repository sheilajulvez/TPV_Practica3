#pragma once
#include "../ecs/Manager.h"
#include "../sdlutils/Font.h"
#include "../utils/checkML.h"
#include "../systems/FighterSystem.h"
#include "../systems/RenderSystem.h"
class GameStateMachine;
class PauseState: public Manager
{
private:
	GameStateMachine* gsm;
	FighterSystem* fightersystem;
	RenderSystem* rendersystem;
	
public:

	PauseState(GameStateMachine* gsm);
	virtual ~PauseState() {

	}
	void setLifes(int i) {
		//health->setHealth(i);
	}
	void setFighterpos(Vector2D pos) {
		//trans_player->setPos(pos);
	}
	//void handleEvents();

	//void update();
	//void render();

};

