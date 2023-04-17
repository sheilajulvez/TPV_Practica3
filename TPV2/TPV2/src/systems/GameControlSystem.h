#pragma once
#include "../ecs/System.h"
#include <SDL.h>
class GameStateMachine;
class GameCtrlSystem : public System {
public:
	GameCtrlSystem(GameStateMachine* gsm) { this->gsm = gsm;};
	constexpr static cmpId_type id = _sys_GAMECTRL;
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego no est� parado y el jugador pulsa SDLK_SPACE cambia el estado
	// como en la pr�ctica 1, etc. Tiene que enviar mensajes correspondientes cuando
	// empieza una ronda o cuando empieza una nueva partida.
	void update() override;
	inline int getstate_() { return state_; };
	inline void setstate_(int s) { state_ = s; };
private:
	// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay m�s vidas avisar que ha acabado el juego (y quien
	// es el ganador).
	void onCollision_FighterAsteroid();
	// Para gestionar el mensaje de que no hay m�s asteroides. Tiene que avisar que
	// ha acabado la ronda y adem�s que ha acabado el juego (y quien es el ganador)
	void onAsteroidsExtinction();
	int winner_; // 0 - None, 1 - Asteroids, 2- Fighter
	int state_; // El estado actual del juego (en lugar del componente State)//Pause=0, Play=1, End=2;
	GameStateMachine* gsm;
};