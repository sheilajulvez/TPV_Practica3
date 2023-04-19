#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"

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

	bool exit;

public:

	virtual ~Game();
	Game();
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
