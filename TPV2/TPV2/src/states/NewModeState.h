#pragma once
#include "../ecs/Manager.h"
#include "../systems/FighterSystem.h"

#include "../systems/RenderSystem.h"
#include "../systems/AsteroidsSystem.h"
#include "../systems/BulletSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../utils/GameStateMachine.h"
#include "../systems/PowerUpSystem.h"

class NewModeState:public Manager
{
public:
	NewModeState(GameStateMachine* g);
	virtual ~NewModeState();
private:
	GameStateMachine* gsm;
	AsteroidsSystem* asteroidsystem;
	BulletsSystem* bulletsystem;
	CollisionsSystem* collisionsystem;
	FighterSystem* fightersystem;
	RenderSystem* rendersystem;
	PowerUpSystem* powerupsystem;
	

};

