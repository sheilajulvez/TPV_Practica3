#include "MultiPlayerState.h"

MultiPlayerState::MultiPlayerState(GameStateMachine* g) {

    
	gsm = g;
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

    if (a == "1") {
        server(PORT);
        isserver = true;
        fightersystem = addSystem<FighterSystem>();
        fightersystem->initSystem();
        
    }
    else {
        // Pregunta por la IP
        cout << "IP: ";
        char host[1024];
        cin >> host;
        client(host, PORT);
        isserver = false;

    }
}


void MultiPlayerState::server(int port) {
    // abre un puerto cualquiera (via de mensajes)
     sd = SDLNet_UDP_Open(port);
    // si no consigue abrir
    if (!sd) {
        throw("ERROR AL ABRIR EL SERVER");
        //error(); 
    }

    // creacion de un packet (estructura de datos a enviar/recibir)
    p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
    // si no consigue crear
    if (!p) {
        throw("ERROR AL CREAR EL PAQUETE");
        //error(); 
    }

    buffer = reinterpret_cast<char*>(p->data);
    socketSet = SDLNet_AllocSocketSet(1);
    SDLNet_UDP_AddSocket(socketSet, sd);

}
void MultiPlayerState::client(char* host, int port) {
    sd = SDLNet_UDP_Open(0); // coge el socket abierto 
    if (SDLNet_ResolveHost(&srvadd, host, port) < 0) {
        throw("ERROR AL ESTABLECER CONEXION CON EL SERVIDOR");
        //error(); 
    }
    // creacion de un packet (estructura de datos a enviar/recibir)
    p = SDLNet_AllocPacket(MAX_PACKET_SIZE);

    buffer = reinterpret_cast<char*>(p->data);
    socketSet = SDLNet_AllocSocketSet(1);
    SDLNet_UDP_AddSocket(socketSet, sd);
}
 MultiPlayerState::~MultiPlayerState() {
     // ESTO DE AQUI DEBE LLAMARSE EN LA DESTRUCTORA DEL JUEGO
   // libera 
    SDLNet_FreePacket(p);
    SDLNet_FreeSocketSet(socketSet);
    SDLNet_UDP_Close(sd);
}


void MultiPlayerState::update() {
    // MODIFICAR ESTE CODIGO PARA QUE SEA NUESTRO JUEGO
    if(isserver){
        // TODO I: PROCESS DATA on socket sd
       //actividad en clientes
        if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {
            if (SDLNet_SocketReady(sd)) {
                if (SDLNet_UDP_Recv(sd, p) > 0) {
                    // print client’s message
                    cout << "Client says: " << buffer << endl;
                    // send a response
                    trans = getComponent<Transform>(getHandler(_HDLR_FIGHTER))->getPos();
                    int size = sizeof(trans);
                    memcpy(p->data, &trans, size);
                    p->len = size;
                    SDLNet_UDP_Send(sd, -1, p);
                }
            }
        }
    }

   
    // MODIFICAR ESTE CODIGO PARA QUE SEA NUESTRO JUEGO
    else {
        // TODO I: PROCESS DATA on socket sd
        cout << "Enter a message: ";
        cin.getline(buffer, 255);

        //if (strcmp(buffer, "exit") == 0) { break; }
        p->len = static_cast<int>(strlen(buffer)) + 1;
        p->address = srvadd;
        SDLNet_UDP_Send(sd, -1, p);
        if (SDLNet_CheckSockets(socketSet, 3000) > 0) {
            if (SDLNet_SocketReady(sd)) {
                while (SDLNet_UDP_Recv(sd, p) > 0) {
                    Vector2D receivedInt;
                    memcpy(&receivedInt, p->data, p->len);
                    cout << "Server says: " << receivedInt << endl;
                }
            }
        }
    }
}

