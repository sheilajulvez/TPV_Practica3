// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include "game/Game.h"
#include "sdlutils/sdlutils_demo.h"
#include "utils/checkML.h"
#include <SDL_net.h>
#include "game/Constantes.h"

void server(int port) {
	// abre un puerto cualquiera (via de mensajes)
	UDPsocket sd = SDLNet_UDP_Open(port);
	// si no consigue abrir
	if (!sd) {
		throw("ERROR AL ABRIR EL SERVER");
		//error(); 
	}

	// creacion de un packet (estructura de datos a enviar/recibir)
	UDPpacket* p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	// si no consigue crear
	if (!p) {
		throw("ERROR AL CREAR EL PAQUETE");
		//error(); 
	}

	char* buffer = reinterpret_cast<char*>(p->data);
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);

	// MODIFICAR ESTE CODIGO PARA QUE SEA NUESTRO JUEGO

	bool end = false;

	while (!end) {
		// TODO I: PROCESS DATA on socket sd
		//actividad en clientes
		if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {
			if (SDLNet_SocketReady(sd)) {
				if (SDLNet_UDP_Recv(sd, p) > 0) {
					// print client’s message
					cout << "Client says: " << buffer << endl;
					// send a response
					memcpy(buffer, "Received!", 10);
					p->len = 10;
					SDLNet_UDP_Send(sd, -1, p);
				}
			}
		}
	}

	// ESTO DE AQUI DEBE LLAMARSE EN LA DESTRUCTORA DEL JUEGO
	// libera 
	SDLNet_FreePacket(p);
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_UDP_Close(sd);
}
void client(char* host, int port) {
	// coge el socket abierto 
	UDPsocket sd = SDLNet_UDP_Open(0);
	IPaddress srvadd; //direcion ip
	if (SDLNet_ResolveHost(&srvadd, host, port) < 0) {
		throw("ERROR AL ESTABLECER CONEXION CON EL SERVIDOR");
		//error(); 
	}
	UDPpacket* p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	char* buffer = reinterpret_cast<char*>(p->data);
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);

	// MODIFICAR ESTE CODIGO PARA QUE SEA NUESTRO JUEGO
	while (1) {
		// TODO I: PROCESS DATA on socket sd
		cout << "Enter a message: ";
		cin.getline(buffer, 255);
		if (strcmp(buffer, "exit") == 0) { break; }
		p->len = static_cast<int>(strlen(buffer)) + 1;
		p->address = srvadd;
		SDLNet_UDP_Send(sd, -1, p);
		if (SDLNet_CheckSockets(socketSet, 3000) > 0) {
			if (SDLNet_SocketReady(sd)) {
				while (SDLNet_UDP_Recv(sd, p) > 0) {
					cout << "Server says: " << buffer << endl;
				}
			}
		}
	}
	//while (!end) {
	//	// TODO I: PROCESS DATA on socket sd
	//	//actividad en clientes
	//	if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {
	//		if (SDLNet_SocketReady(sd)) {
	//			if (SDLNet_UDP_Recv(sd, p) > 0) {
	//				// print client’s message
	//				cout << "Client says: " << buffer << endl;
	//				// send a response
	//				memcpy(buffer, "Received!", 10);
	//				p->len = 10;
	//				SDLNet_UDP_Send(sd, -1, p);
	//			}
	//		}
	//	}
	//}

	// ESTO DE AQUI DEBE LLAMARSE EN LA DESTRUCTORA DEL JUEGO
	SDLNet_FreePacket(p);
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_UDP_Close(sd);
}


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
	if (SDL_Init(0) == -1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	if (SDLNet_Init() == -1) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}

	cout << "1 para server\n2 para cliente" << endl;
	string a;
	cin >> a;

	if (a == "1") server(PORT);
	else {
		// Pregunta por la IP
		cout << "IP: ";
		char host[1024];
		cin >> host;
		client(host, PORT);
	}
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

