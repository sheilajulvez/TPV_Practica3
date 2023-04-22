#pragma once
#include "../game/ecs_defs.h"
#include <string>
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
	std::string my_name;
};
struct BulletPositionMessage :NETMessage {
	float posx;
	float posy;
	float velx;
	float vely;

	float r;
};

struct PlayerWins :NETMessage {
	std::string name;
};
struct RoundStart :NETMessage {
	
};



