#pragma once
#include "../ecs/Manager.h"
#include "../utils/GameStateMachine.h"
#include <SDL_net.h>
#include "../systems/FighterSystem.h"
#include "../systems/RenderSystem.h"
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

public:
	MultiPlayerState(GameStateMachine* g);
	virtual ~MultiPlayerState();
	void server(int port);
	void client(char* host, int port);
	void update();





};

