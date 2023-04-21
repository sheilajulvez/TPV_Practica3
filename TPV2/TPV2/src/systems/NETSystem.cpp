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
    // creacion de un packet (estructura de datos a enviar/recibir)
    p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
    // si no consigue crear
    if (!p) {
        throw("ERROR AL CREAR EL PAQUETE");
        //error(); 
    }
    message = reinterpret_cast<NETMessage*>(p->data);
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
   // SDLNet_ResolveHost(&srvadd, "localhost", port);
   
   /* socketSet = SDLNet_AllocSocketSet(1);
    SDLNet_UDP_AddSocket(socketSet, sd);*/

}
void NETSystem::client(char* host, int port) {
   
    sd = SDLNet_UDP_Open(0); // coge el socket abierto 
    if (!sd)
        throw SDLNet_GetError();

    if (SDLNet_ResolveHost(&srvadd, host, port) < 0) {
        throw("ERROR AL ESTABLECER CONEXION CON EL SERVIDOR");
        //error(); 
    }

    socketSet = SDLNet_AllocSocketSet(1);
    SDLNet_UDP_AddSocket(socketSet, sd);


    //SI RECIBE LA CONEXION ANTES DE 3 SEGUNDOS LA ESTABLECE
    if (SDLNet_CheckSockets(socketSet, 3000))
    {
        //Si estamos ready
        if (SDLNet_SocketReady(sd))
        {
            //if (SDLNet_UDP_Recv(sd, p) > 0)
            //{
            //    //Si es un mensaje de bienvenida
            //    //estamos listos para empezar el juego
            //    if (m_->_type == _WELCOME_)
            //    {
            //        isGameReday_ = true;
            //        WelcomeMsg* m = static_cast<WelcomeMsg*>(m_);
            //        remotePlayerName_ = std::string(
            //            reinterpret_cast<char*>(m->name));
            //        id_ = m->id;
            //        names_[id_] = localPlayerName_;
            //        names_[1 - id_] = remotePlayerName_;
            //    }
            //}
        }
    }

    // free the socket set, won't be used anymore
    SDLNet_FreeSocketSet(socketSet);
}

void NETSystem::update() {
    while (SDLNet_UDP_Recv(sd, p) > 0) {

        switch (message->type) {
        case _FighterPositionMessage_:

            FighterPositionMessage* m = static_cast<FighterPositionMessage*>(message);
            Vector2D pos = { m->posx,m->posy };
            float r = m->rot;
            mngr_->getSystem<FighterSystem>()->SetTrans(getID(),pos,r);
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
    p->len = sizeof(FighterPositionMessage);
    p->address = srvadd;

    // send the message
    SDLNet_UDP_Send(sd, -1, p);

}