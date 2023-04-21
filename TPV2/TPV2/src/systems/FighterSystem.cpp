#include "FighterSystem.h"
#include "BulletSystem.h"
#include "../ecs/Manager.h"

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void FighterSystem::receive(const Message& m) {
	switch (m.id)
	{
	case M_ROUND_START: onRoundStart(); break;
	case M_ROUND_OVER_: onRoundOver(); break;
	case M_COLLISION_FIGHTER_ASTEROID:onCollision_FighterAsteroid(); break;
	case M_PAUSE: active_ = false; break;
	default:
		break;
	}
}
// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
// correspondiente, etc.
void FighterSystem::initSystem() {
	netsystem = mngr_->getSystem<NETSystem>();
	if (netsystem!=nullptr) {
		fighter2 = mngr_->addEntity(_grp_GENERAL);
		mngr_->setHandler(_HDLR_NETFIGHTER_2, fighter2);
		t2 = mngr_->addComponent<Transform>(fighter2);
		t2->setPos(POS2);
		t2->setW(PWIDTH);
		t2->setH(PHEIGHT);

		mngr_->addComponent<Health>(fighter2);
	}
	fighter = mngr_->addEntity(_grp_GENERAL);
	mngr_->setHandler(_HDLR_FIGHTER, fighter);
	t1=mngr_->addComponent<Transform>(fighter);
	mngr_->addComponent<Health>(fighter);

	
	t1->setPos(POS1);
	t1->setW(PWIDTH);
	t1->setH(PHEIGHT);

	//mngr_->addComponent<Image>(fighter);
	

}
// Si el juego está parado no hacer nada, en otro caso actualizar la velocidad
// del caza y moverlo como en la prácticaaaaaaaaaaa 1 (acelerar, desacelerar, etc). Además, 
// si el juego no está parado y el jugador pulsa la tecla de disparo, enviar un
// mensaje con las características físicas de la bala. Recuerda que se puede disparar
// sólo una bala cada 0.25sec.

void FighterSystem::update() {
	
	if (netsystem != nullptr) {
		Uint8 myId = netsystem->getID();
		if (myId == 0)
			move(fighter);
		else
			move(fighter2);
	}
	else {
		move(fighter);
	}
	
}

void FighterSystem::SetTrans(int id, Vector2D pos, float r) {
	if (id == 0) {
		trans_player = mngr_->getComponent<Transform>(fighter2);
		trans_player->setPos(pos);
		trans_player->setR(r);
	}	
	else {
		trans_player = mngr_->getComponent<Transform>(fighter);
		trans_player->setPos(pos);
		trans_player->setR(r);

	}
		

}
void FighterSystem::move(Entity* f) {
	
	trans_player = mngr_->getComponent<Transform>(f);
	if (active_) {
		SDL_Event event_;

		InputHandler::instance()->update(event_);

		if (InputHandler::instance()->keyDownEvent()) {
			if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
				frames = sdlutils().currRealTime() - start;
				if (frames >= 250) {
					Pium->play();
					start = totaltime;
					frames = 0;
					start = sdlutils().currRealTime();
					Message m;
					m.id = M_BULLET_SPAWN;
					m.bullet_spawn.pos = trans_player->getPos()
						+ Vector2D(trans_player->getW() / 2.0f, trans_player->getH() / 2.0f)
						- Vector2D(0.0f, trans_player->getH() / 2.0f + 5.0f + 12.0f).rotate(trans_player->getR())
						- Vector2D(2.0f, 10.0f);


					m.bullet_spawn.vel = Vector2D(0.0f, -1.0f).rotate(trans_player->getR()) * (trans_player->getVel().magnitude() + 5.0f);
					m.bullet_spawn.width = 5;
					m.bullet_spawn.height = 20;
					m.bullet_spawn.rotation = trans_player->getR();
					mngr_->getSystem<BulletsSystem>()->receive(m);

				}
			}

			if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
				trans_player->setR(trans_player->getR() + 5);
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
				trans_player->setR(trans_player->getR() - 5);
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_UP)) {
				thrust->play();
				if (sqrt(pow(trans_player->getVel().getX(), 2) + pow(trans_player->getVel().getY(), 2)) < 4) {
					trans_player->setVel(trans_player->getVel() + (Vector2D(0, -1).rotate(trans_player->getR()) * ACCELERATION));
				}
				else {
					trans_player->setVel(trans_player->getVel().normalize() * 4);
				}
			}

		}

		trans_player->setVel(trans_player->getVel() * DEACCELERATION);

		if (sqrt(pow(trans_player->getVel().getX(), 2) + pow(trans_player->getVel().getY(), 2)) < MIN) {
			trans_player->setVel(Vector2D(0, 0));
		}

		if (trans_player->getPos().getX() > (WIN_WIDTH + trans_player->getW())) {
			trans_player->setPos({ 0,trans_player->getPos().getY() });
		}
		else if (trans_player->getPos().getX() + trans_player->getW() < 0) {
			trans_player->setPos({ WIN_WIDTH,trans_player->getPos().getY() });

		}
		if (trans_player->getPos().getY() > (WIN_HEIGHT + trans_player->getH())) {
			trans_player->setPos({ trans_player->getPos().getX(), 0 });
		}
		else if (trans_player->getPos().getY() + trans_player->getH() < 0) {
			trans_player->setPos({ trans_player->getPos().getX(), WIN_HEIGHT });
		}
		trans_player->setPos(trans_player->getPos() + trans_player->getVel());

		if (netsystem != nullptr) {
			mngr_->getSystem<NETSystem>()->SendFighterPosition(trans_player->getPos(), trans_player->getR());
		}

	}
		
}
// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotación 0. No
	// hace falta desactivar la entidad (no dibujarla si el juego está parado).
void FighterSystem::onCollision_FighterAsteroid() {
	Transform* trans_player = mngr_->getComponent<Transform>(fighter);
	trans_player->setPos({ WIN_WIDTH / 2, WIN_HEIGHT / 2 });
	trans_player->setVel({ 0,0 });
	trans_player->setR(0);
}
// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
void FighterSystem::onRoundOver() {
	active_ = false;

}
// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void FighterSystem::onRoundStart() {
	active_ = true;
}
