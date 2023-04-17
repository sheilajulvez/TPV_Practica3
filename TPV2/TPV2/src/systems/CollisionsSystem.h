#pragma once
#include "../ecs/System.h"
#include "../utils/Collisions.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../components/Health.h"
#include "../sdlutils/SoundEffect.h"

class CollisionsSystem : public System {
public:
	constexpr static cmpId_type id = _sys_COLLISIONS;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
	// en la práctica 1 y enviar mensajes correspondientes.
	void update() override;
private:
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;
	Transform* trans_asteroid;
	Entity* fighter;
	Transform* trans_player;
	Health* health;
	Transform* trans_bullet;
	SoundEffect* crash;
	SoundEffect* bullet_asteroid;

};
