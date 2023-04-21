#pragma once
#include "../ecs/Manager.h"
#include "../utils/GameStateMachine.h"
#include <SDL_net.h>
#include "../systems/FighterSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/NETSystem.h"
#include "../systems/BulletSystem.h"
#include "../systems/CollisionsSystem.h"
class MultiPlayerState:public Manager
{

private:
	GameStateMachine* gsm;
	UDPsocket sd;
	UDPpacket* p;
	char* buffer;
	SDLNet_SocketSet socketSet;
	IPaddress srvadd;//direccion ip
	bool isserver;
	FighterSystem* fightersystem;
	Vector2D trans;
	RenderSystem* rendersystem;
	NETSystem* netsystem;
	BulletsSystem* bulletsystem;
	CollisionsSystem* collision;
public:
	MultiPlayerState(GameStateMachine* g);
	virtual ~MultiPlayerState();
	
	





};

