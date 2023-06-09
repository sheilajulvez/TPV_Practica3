#pragma once
#include "../ecs/System.h"
#include "../utils/Collisions.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../components/Health.h"
#include "../sdlutils/SoundEffect.h"
#include "NETSystem.h"
#include "PowerUpSystem.h"
#include "../components/PowerComponent.h"
class CollisionsSystem : public System {
public:
	constexpr static  sysId_type id = _sys_COLLISIONS;
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego est� parado no hacer nada, en otro caso comprobar colisiones como
	// en la pr�ctica 1 y enviar mensajes correspondientes.
	void update() override;
private:
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_;
	Transform* trans_asteroid;
	Entity* fighter;
	Entity* fighter2;
	Transform* trans_player;
	Transform* trans_player2;
	Health* health;
	Health* health2;
	Transform* trans_bullet;
	SoundEffect* crash;
	SoundEffect* bullet_asteroid;
	NETSystem* netsystem;
	int rand;
	PowerUpSystem* p;
	Transform* trans_power1;
	PowerComponent* powercomponent;
	bool power;
	


};
