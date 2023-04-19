#pragma once
#include "../ecs/Manager.h"
#include "../utils/GameStateMachine.h"
class MultiPlayerState:public Manager
{
private:
	GameStateMachine* gsm;

public:
	MultiPlayerState(GameStateMachine* g);
	virtual ~MultiPlayerState() {}





};

