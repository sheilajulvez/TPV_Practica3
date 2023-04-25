#pragma once
#include "../ecs/System.h"
#include <SDL_net.h>
#include "../ecs/NETMessage.h"
class NETSystem:public System
{
private:
	char* host;
	char* player1;
	char* player2;
	int port;
	bool isserver;
	UDPsocket sd;
	UDPpacket* p;
	NETMessage* message;

	SDLNet_SocketSet socketSet;
	IPaddress srvadd;//direccion ip

	char my_name[10];
	char other_name[10];
public:
	NETSystem();
	constexpr static sysId_type id = _sys_NET;
	virtual ~NETSystem(){}
	void setContext(Manager* mngr) {
		mngr_ = mngr;
	}
	 void initSystem();
	 void update();
	 void server(int p);
	 void client(char* h, int p);
	 int getID();

	 void SendFighterPosition(Vector2D pos, float r);
	 void SendBulletSpawn(Vector2D pos, Vector2D v,float r);
	 void SendRoundStart();
	 void SetWaitingTetxt(bool t);

	 inline string get_MyName() {
		 return my_name;
	 }
	
	 inline string get_otherName() {
		 return other_name;
	 }
	//virtual void receive(const Message& m) { }

};

