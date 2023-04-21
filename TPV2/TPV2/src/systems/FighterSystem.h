#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"
#include "../systems/NETSystem.h"

class FighterSystem: public System {
public:
	constexpr static  sysId_type id = _sys_FIGHTER;
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
	// correspondiente, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso actualizar la velocidad
	// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc). Además, 
	// si el juego no está parado y el jugador pulsa la tecla de disparo, enviar un
	// mensaje con las características físicas de la bala. Recuerda que se puede disparar
	// sólo una bala cada 0.25sec.
	void move(Entity* f);
	void update() override;
	inline Entity* getPlayer() {
		return fighter;
	}
	inline Entity* getPlayer2() {
		return fighter2;
	}
	void SetTrans(int id, Vector2D p, float r);
private:
	// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotación 0. No
	// hace falta desactivar la entidad (no dibujarla si el juego está parado).
	void onCollision_FighterAsteroid();
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)


	bool active_;
	float totaltime, start= sdlutils().currRealTime(), frames;
	Entity* fighter;
	Entity* fighter2;
	Transform* trans_player;
	Transform* t1;
	Transform* t2;
	NETSystem* netsystem;

	SoundEffect* thrust = &SDLUtils::instance()->soundEffects().at("thrust");
	SoundEffect* Pium = &SDLUtils::instance()->soundEffects().at("fire");
	
};
