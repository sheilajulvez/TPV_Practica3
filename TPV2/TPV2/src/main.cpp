// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include "game/Game.h"
#include "sdlutils/sdlutils_demo.h"
#include "utils/checkML.h"
#include <SDL_net.h>

int main(int ac, char **av) {
	//try {
	//	sdlutils_basic_demo();
	//} catch (const std::string &e) { // catch exceptions thrown as strings
	//	std::cerr << e << std::endl;
	//} catch (const char *e) { // catch exceptions thrown as char*
	//	std::cerr << e << std::endl;
	//} catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
	//	std::cerr << e.what();
	//} catch (...) {
	//	std::cerr << "Caught and exception of unknown type ...";
	//}
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game::instance();
	Game::instance()->init();
	Game::instance()->run();
	//Game::instance()->free();
	delete Game::instance();
	if (SDLNet_Init() < 0) {
		//error();
	}


	
	//bool soyserver = true;
	//int port = 9999;
	//if (soyserver) {
	//	IPaddress ip;
	//	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) { //error(); 
	//	}
	//	TCPsocket masterSocket = SDLNet_TCP_Open(&ip);
	//	if (!masterSocket) { //error(); 
	//	}
	//	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
	//	SDLNet_TCP_AddSocket(socketSet, masterSocket);
	//	while (true) {

	//		if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {
	//			// TODO I: process connection request on masterSocket
	//			char buffer[256];
	//			int result = 0;
	//			if (SDLNet_SocketReady(masterSocket)) {
	//				TCPsocket client = SDLNet_TCP_Accept(masterSocket);
	//				result = SDLNet_TCP_Recv(client, buffer, 255);
	//				if (result > 0) {
	//					cout << "Client says: " << buffer << endl;
	//					SDLNet_TCP_Send(client, "Received!", 10);
	//				}
	//				SDLNet_TCP_Close(client);
	//			}

	//		}

	//	}
	//	SDLNet_FreeSocketSet(socketSet);
	//	SDLNet_TCP_Close(masterSocket);
	//}
	//else {
	//	//'10.8.117.53'
	//	char buffer[256];
	//	int result = 0;
	//	IPaddress ip;
	//	if (SDLNet_ResolveHost(&ip, "10.8.117.53", port) < 0) { //error(); 
	//	}
	//	TCPsocket client = SDLNet_TCP_Open(&ip);
	//	if (!client) { //error(); 
	//	}
	//	result = SDLNet_TCP_Recv(client, buffer, 255);
	//	if (result > 0) {
	//		cout << "Server says: " << buffer << endl;
	//		//SDLNet_TCP_Send(client, "Received!", 10);
	//	}
	//	// TODO: SEND MSG AND WAIT FOR RESPONSE
	//	SDLNet_TCP_Close(client);
	//}
	//

	SDLNet_Quit();
	return 0;
}

