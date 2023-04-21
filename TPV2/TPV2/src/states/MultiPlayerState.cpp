#include "MultiPlayerState.h"

MultiPlayerState::MultiPlayerState(GameStateMachine* g) {

    this->gsm = g;
    netsystem = addSystem<NETSystem>();
    fightersystem = addSystem<FighterSystem>();
    rendersystem = addSystem<RenderSystem>(1);
    bulletsystem = addSystem<BulletsSystem>();
    collision = addSystem<CollisionsSystem>();
    gamecontrolsystem = addSystem<GameCtrlSystem>(gsm);
    Message m;
    m.id = M_ROUND_START;
    send(m);
   
    /*netsystem->initSystem();
    fightersystem->initSystem();
    rendersystem->initSystem();*/
    

    
    
	gsm = g;
    

    
}



 MultiPlayerState::~MultiPlayerState() {
     // ESTO DE AQUI DEBE LLAMARSE EN LA DESTRUCTORA DEL JUEGO
   // libera 
    SDLNet_FreePacket(p);
    SDLNet_FreeSocketSet(socketSet);
    SDLNet_UDP_Close(sd);
    //Uwuuuuu
}




