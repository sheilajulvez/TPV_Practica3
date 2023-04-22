#pragma once
#include "../game/ecs_defs.h"

struct NETMessage
{
	NETmsgId_type type;
};
struct FighterPositionMessage :NETMessage {
	float posx;
	float posy;
	int velx;
	int vely;
	
	float rot;
	
};
struct PlayRequestMsg :NETMessage {
	int name;
};
struct BulletPositionMessage :NETMessage {
	float posx;
	float posy;
	float velx;
	float vely;

	float r;
};
struct RoundStart :NETMessage {
	
};



