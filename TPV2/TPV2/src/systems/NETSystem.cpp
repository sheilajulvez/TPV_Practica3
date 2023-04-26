#include "NETSystem.h"
#include "../ecs/Manager.h"
#include "FighterSystem.h"
#include "BulletSystem.h"
#include "RenderSystem.h"
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
        cout << "Dime tu nombre" << endl;
        string m;
        cin >> m;
        for (int i = 0; i < m.length(); i++) {
            my_name[i] = m[i];
        }
       
        SetWaitingTetxt(true);
        server(PORT);
    }
    else {
        // Pregunta por la IP
        cout << "IP: ";
        char host[1024];
        cin >> host;
        cout << "Dime tu nombre" << endl;
        isserver = false;
        for (int i = 0; i < 10; i++) {
            cin >> my_name[i];
        }
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

    //SDLNet_ResolveHost(&srvadd, "192.168.1.147", port);
   
   /* socketSet = SDLNet_AllocSocketSet(1);
    SDLNet_UDP_AddSocket(socketSet, sd);*/


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

    PlayRequestMsg* m = static_cast<PlayRequestMsg*>(message);
    m->type = _I_WANT_TO_PLAY;
    
    strcpy_s(my_name, m->my_name);
    p->len = sizeof(PlayRequestMsg);
    p->address = srvadd;
    SDLNet_UDP_Send(sd, -1, p);
   

}

void NETSystem::update() {
    
    while (SDLNet_UDP_Recv(sd, p) > 0) {
        lastmsg= SDL_GetTicks();
        switch (message->type) {

            case _I_WANT_TO_PLAY: {
                // we accept the connection if the player is the master, and no other player is connected
                if (isserver) {
                    started = true;
                    srvadd = p->address;
                    PlayRequestMsg* m = static_cast<PlayRequestMsg*>(message);
                    strcpy_s(m->my_name, other_name);

                    PlayRequestMsg* me = static_cast<PlayRequestMsg*>(message);
                    me->type = _I_WANT_TO_PLAY;
                    
                    strcpy_s(my_name, m->my_name);
                    p->len = sizeof(PlayRequestMsg);
                   
                    p->address = srvadd;
                    SDLNet_UDP_Send(sd, -1, p);
                    SetWaitingTetxt(false);


                }
                else {
                    PlayRequestMsg* m = static_cast<PlayRequestMsg*>(message);
                    
                    strcpy_s(m->my_name, other_name);
                }
                break;
            }
            case _FighterPositionMessage_: {

                FighterPositionMessage* m = static_cast<FighterPositionMessage*>(message);
                Vector2D pos = { m->posx,m->posy };
                float r = m->rot;
                mngr_->getSystem<FighterSystem>()->SetTrans(getID(), pos, r);
                break;
            }
            case _BulletPositionMessage_: {
                BulletPositionMessage* m = static_cast<BulletPositionMessage*>(message);
                Vector2D pos = { m->posx,m->posy };
                float r = m->r;
                Vector2D vel = { m->velx,m->vely };
                mngr_->getSystem<BulletsSystem>()->createBullet(pos, vel, r);
                break;
            }
            case _Round_Start_: {
                RoundStart* mes = static_cast<RoundStart*>(message);
                Message m;
                m.id = M_ROUND_START;
                mngr_->send(m);

            }
            case _PlayerWins: {

                PlayerWins* m= static_cast<PlayerWins*>(message);
                Message mr;
                mr.id = PLAYER1_WIN;
                mngr_->send(mr);
            
                mngr_->getSystem<RenderSystem>()->setText(m->name);


            }
        }
    
    }
    if (started && SDL_GetTicks() - lastmsg > 3000) {
        started = false;
        SetWaitingTetxt(true);
        int id = getID();
        Vector2D po;
        if (id == 0)po = POS1;
        else po = POS2;
        mngr_->getSystem<FighterSystem>()->SetTrans(id,po,0);
        if (!isserver) {
            SDLNet_UDP_Close(sd);
            sd = SDLNet_UDP_Open(PORT);
            isserver = true;

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

void NETSystem::SendBulletSpawn(Vector2D pos, Vector2D v, float r) {

    BulletPositionMessage* m= static_cast<BulletPositionMessage*>(message);
    m->type = _BulletPositionMessage_;
   
    m->posx = pos.getX();
    m->posy = pos.getY();
    m->r = r;
    m->velx = v.getX();
    m->vely = v.getY();

    p->len =sizeof(BulletPositionMessage);
    p->address = srvadd;

    // send the message
    SDLNet_UDP_Send(sd, -1, p);


}
void NETSystem::SendRoundStart() {

    RoundStart* mes = static_cast<RoundStart*>(message);
    mes->type = _Round_Start_;
    p->len = sizeof(RoundStart);
    p->address = srvadd;
    SDLNet_UDP_Send(sd, -1, p);
}

void NETSystem::SetWaitingTetxt(bool t) {
    if (t) {
        mngr_->getSystem<RenderSystem>()->setText("WAITING FOR OTHER PLAYER");
    }
    else {
        mngr_->getSystem<RenderSystem>()->setText(" ");
    }

}