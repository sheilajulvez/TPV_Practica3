#include "NETSystem.h"
#include "../ecs/Manager.h"
#include "FighterSystem.h"
NETSystem::NETSystem() {
    isserver = false;

}
void NETSystem::initSystem() {
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
        isserver = true;
        server(PORT);
       

    }
    else {
        // Pregunta por la IP
        cout << "IP: ";
        char host[1024];
        cin >> host;
        isserver = false;
        client(host, PORT);
        

    }
}

void NETSystem::server(int port) {
    // abre un puerto cualquiera (via de mensajes), abre socket
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

    message = reinterpret_cast<NETMessage*>(p->data);
    socketSet = SDLNet_AllocSocketSet(1);
    SDLNet_UDP_AddSocket(socketSet, sd);

}
void NETSystem::client(char* host, int port) {
    sd = SDLNet_UDP_Open(0); // coge el socket abierto 
    if (SDLNet_ResolveHost(&srvadd, host, port) < 0) {
        throw("ERROR AL ESTABLECER CONEXION CON EL SERVIDOR");
        //error(); 
    }
    // creacion de un packet (estructura de datos a enviar/recibir)
    p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
    message = reinterpret_cast<NETMessage*>(p->data);

    socketSet = SDLNet_AllocSocketSet(1);
    SDLNet_UDP_AddSocket(socketSet, sd);
}

void NETSystem::update() {
    while (SDLNet_UDP_Recv(sd, p) > 0) {

        switch (message->type) {
        case _FighterPositionMessage_:

            FighterPositionMessage* m = static_cast<FighterPositionMessage*>(message);
            Vector2D pos = { m->posx,m->posy };
            float r = m->rot;
            mngr_->getSystem<FighterSystem>()->SetTrans(getID());
            break;
            
        }


    }
    
}

int NETSystem::getID() {
    if (isserver)return 0;
    else return 1;
}


void NETSystem::SendFighterPosition(Vector2D pos, float r) {
    // we prepare a message that includes all information
    FighterPositionMessage* m = static_cast<FighterPositionMessage*>(message);
    m->type = _FighterPositionMessage_;
    m->posx = pos.getX();
    m->posy = pos.getY();
    m->rot = r;

    // set the message length and the address of the other player
    p->len = sizeof(m);
    p->address = srvadd;

    // send the message
    SDLNet_UDP_Send(sd, -1, p);

}