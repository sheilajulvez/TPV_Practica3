#pragma once
#include "../ecs/System.h"
#include "../ecs/Message.h"
#include "../sdlutils/RandomNumberGenerator.h"
class PowerUpSystem: public System
{
public :
	constexpr static sysId_type id = _sys_POWERUP;
	PowerUpSystem();
	virtual ~PowerUpSystem();
	void receive(const Message& m);
	void newPowerUp(Entity* ast);
	void CollisionPowerUp1(Entity* p);
private:
	int rand;
};

