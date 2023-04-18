#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include <SDL_net.h>

#pragma once
using namespace std;

using uint = unsigned int;
const uint FRAME_RATE = 3;// número de frames que tardará en actualizarse el juego
class GameStateMachine;

class Game :public Singleton <Game>
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStMc=nullptr;
	UDPpacket* p;
	UDPsocket calcetin;
	bool exit;

public:

	virtual ~Game();
	Game(char* host,int port);
	void handleEvents();
	void render();
	void update();
	void run();// blucle de 
	void free_();
	void exit_() {
		exit = true;
	};
	SDL_Renderer* getRenderer() {
		return SDLUtils::instance()->renderer();

	};
};
