#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"

class RenderSystem : public System {
public:
	RenderSystem(int state_);
	constexpr static sysId_type id = _sys_RENDER;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
	// la práctica 1)
	void update() override;

	void setText(string t) {
		text = t;
	}
private:
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. 
	void onRoundStart();
	void onRoundOver();
	void onGameStart();
	void onGameOver(bool winner);
	int winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	int state_; // El estado actual de juego (como en GameCtrlSystem)//Pause=0, Play=1, End=2
	Texture* fighter_texture;
	Texture* health_texture;
	Texture* black_asteroids;
	Texture* gold_asteroids;
	Texture* bullet_texture;
	Font* f;
	SDL_Renderer* renderer;
	SDL_Rect dest;
	SDL_Rect health;
	Transform* trans;
	int n_health;

	string text=" ";
	
};