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
enum MessageType {


};

