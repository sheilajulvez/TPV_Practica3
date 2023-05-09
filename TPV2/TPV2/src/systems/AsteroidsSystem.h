#pragma once
#include "../ecs/System.h"
#include "../sdlutils/RandomNumberGenerator.h"
class AsteroidsSystem : public System {
public:
	constexpr static  sysId_type id = _sys_ASTEROIDS;
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego est� parado no hacer nada, en otro caso mover los asteroides como
	// en la pr�ctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
	// de los 10 al principio de cada ronda).
	void update() override;
private:
	// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide �a� y crear 2 asteroides como en la pr�ctica 1,
	// y si no hay m�s asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(Entity* a,bool p);

	void  createone(int w, int h, int size, Entity* father);
	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
	// asteroides, y desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
	// a�adir los asteroides iniciales (como en la pr�ctica 1).
	void onRoundStart();

	void createAsteroids(int n);
	// El n�mero actual de asteroides en el juego (recuerda que no puede superar un
	// l�mite)

	int numOfAsteroids_;
	// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_;

	int A_fils = 6;
	int A_cols = 5;
	RandomNumberGenerator* random;
	int frequency = 5000;
	int  frames = 50;
	int start_t = 0;
	int framed_time = 0;
	
};
