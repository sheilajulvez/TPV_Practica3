#include "CollisionsSystem.h"
#include "../ecs/Manager.h"
#include "AsteroidsSystem.h"
#include "BulletSystem.h"
#include "FighterSystem.h"




void CollisionsSystem::receive(const Message& m) {
	switch (m.id) {
	case M_ROUND_OVER_:
		onRoundOver();
		break;
	case M_ROUND_START:
		onRoundStart();
		break;
	}
}
// Inicializar el sistema, etc.
void CollisionsSystem::initSystem() {
	fighter = mngr_->getHandler(_HDLR_FIGHTER);
	
	trans_player = mngr_->getComponent<Transform>(mngr_->getHandler(_HDLR_FIGHTER));
	
	health = mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_FIGHTER));
	
	crash = &SDLUtils::instance()->soundEffects().at("explosion");
	bullet_asteroid = &SDLUtils::instance()->soundEffects().at("largewave");
	netsystem = mngr_->getSystem<NETSystem>();

	if (netsystem != nullptr) {
		fighter2 = mngr_->getHandler(_HDLR_NETFIGHTER_2);
		trans_player2 = mngr_->getComponent<Transform>(mngr_->getHandler(_HDLR_NETFIGHTER_2));
		health2 = mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_NETFIGHTER_2));
	}

	p = mngr_->getSystem<PowerUpSystem>();
}

// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
// en la práctica 1 y enviar mensajes correspondientes.
void CollisionsSystem::update() {

	if (active_) {
		vector<Entity*> asteroidsgold = mngr_->getEntitiesByGroup(_grp_ASTEROIDS_GOLD);
		vector<Entity*> asteroidsblack = mngr_->getEntitiesByGroup(_grp_ASTEROIDS_BLACK);
		vector<Entity*> bullets = mngr_->getEntitiesByGroup(_grp_BULLET);
		vector<Entity*> powerup1 = mngr_->getEntitiesByGroup(_grp_POWERUP);
		//MULTIJUGADOR
		if (netsystem != nullptr) {
			for (auto b : bullets) {
				trans_bullet = mngr_->getComponent<Transform>(b);
				if (Collisions::collidesWithRotation(trans_bullet->getPos(), trans_bullet->getW(), trans_bullet->getH(), trans_bullet->getR(),
					trans_player->getPos(), trans_player->getW(), trans_player->getH(), trans_player->getR())) {
					Message m;
					bullet_asteroid->play();
					m.id = M_COLLISION_BULLET_ASTEROID;
					m.asteroid_collision_bullet.a = b;
					mngr_->getSystem<BulletsSystem>()->receive(m);
					
					m.id = M_COLLISION_FIGHTER;
					m.f.f = fighter;
					mngr_->send(m);
				}
				if (Collisions::collidesWithRotation(trans_bullet->getPos(), trans_bullet->getW(), trans_bullet->getH(), trans_bullet->getR(),
					trans_player2->getPos(), trans_player2->getW(), trans_player2->getH(), trans_player2->getR())) {
					Message m;
					bullet_asteroid->play();
					m.id = M_COLLISION_BULLET_ASTEROID;
					m.asteroid_collision_bullet.a = b;
					mngr_->getSystem<BulletsSystem>()->receive(m);

					m.id = M_COLLISION_FIGHTER;
					m.f.f = fighter2;
					mngr_->send(m);

				}
			}
			/*if (Collisions::collidesWithRotation(trans_player->getPos(), trans_player->getW(), trans_player->getH(), trans_player->getR(),
				trans_player2->getPos(), trans_player2->getW(), trans_player2->getH(), trans_player2->getR())) {
				health->LessHealth();
				health2->LessHealth();
			}*/
		}
		
		else{
			for (auto e : asteroidsgold) {
				trans_asteroid = mngr_->getComponent<Transform>(e);
				if (Collisions::collidesWithRotation(trans_player->getPos(), trans_player->getW(), trans_player->getH(), trans_player->getR(),
					trans_asteroid->getPos(), trans_asteroid->getW(), trans_asteroid->getH(), trans_asteroid->getR()))
				{
					Message m;
					if (mngr_->getSystem<FighterSystem>()->getvidainfinita()==false) {
						crash->play();
					}
					
					m.id = M_COLLISION_FIGHTER_ASTEROID;
					mngr_->send(m);


				}
				for (auto b : bullets) {
					trans_bullet = mngr_->getComponent<Transform>(b);
					
					if (Collisions::collidesWithRotation(trans_bullet->getPos(), trans_bullet->getW(), trans_bullet->getH(), trans_bullet->getR(),
						trans_asteroid->getPos(), trans_asteroid->getW(), trans_asteroid->getH(), trans_asteroid->getR())) {
						
						Message m;
						m.id = M_COLLISION_BULLET_ASTEROID;
						m.asteroid_collision_bullet.a = b;
						mngr_->getSystem<BulletsSystem>()->receive(m);
						m.asteroid_collision_bullet.a = e;
						m.asteroid_collision_bullet.power = mngr_->getComponent<PowerComponent>(b)->get();
						mngr_->getSystem<AsteroidsSystem>()->receive(m);
						bullet_asteroid->play();

						if (p != nullptr) {
							rand = sdlutils().rand().nextInt(0, 2);
							if (rand == 0) {
								p->receive(m);
							}
							else {
								p->receive(m);
								
							}
						}
					}
				}
			}
			for (auto e : asteroidsblack) {
				trans_asteroid = mngr_->getComponent<Transform>(e);
				if (Collisions::collidesWithRotation(trans_player->getPos(), trans_player->getW(), trans_player->getH(), trans_player->getR(),
					trans_asteroid->getPos(), trans_asteroid->getW(), trans_asteroid->getH(), trans_asteroid->getR()))
				{
					if (mngr_->getSystem<FighterSystem>()->getvidainfinita() == false) {
						crash->play();
					}
					Message m;
					m.id = M_COLLISION_FIGHTER_ASTEROID;
					mngr_->send(m);

				}
				for (auto b : bullets) {
					trans_bullet = mngr_->getComponent<Transform>(b);
					if (Collisions::collidesWithRotation(trans_bullet->getPos(), trans_bullet->getW(), trans_bullet->getH(), trans_bullet->getR(),
						trans_asteroid->getPos(), trans_asteroid->getW(), trans_asteroid->getH(), trans_asteroid->getR())) {
						Message m;
						bullet_asteroid->play();
						m.id = M_COLLISION_BULLET_ASTEROID;
						m.asteroid_collision_bullet.a = b;
						mngr_->getSystem<BulletsSystem>()->receive(m);
						m.asteroid_collision_bullet.a = e;
						m.asteroid_collision_bullet.power = mngr_->getComponent<PowerComponent>(b)->get();
						mngr_->getSystem<AsteroidsSystem>()->receive(m);

						if (p != nullptr) {
							rand = sdlutils().rand().nextInt(0, 2);
							if (rand == 0 ) {
								p->receive(m);
							}
							else {
								p->receive(m);
							}
						}

					}
				}
			}

			for (auto p : powerup1) {
				trans_power1 = mngr_->getComponent<Transform>(p);
				if (Collisions::collidesWithRotation(trans_player->getPos(), trans_player->getW(), trans_player->getH(), trans_player->getR(),
					trans_power1->getPos(), trans_power1->getW(), trans_power1->getH(), trans_power1->getR())) {
					Message m;
					m.id = M_COLLISION_POWERUP1;
					m.f.f = p;
					m.f.pepe = mngr_->getComponent<PowerComponent>(p)->get();
					mngr_->send(m);

				}
			}
		}
		
	}
}
// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
void CollisionsSystem::onRoundOver() {
	active_ = false;

}
// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void CollisionsSystem::onRoundStart() {
	active_ = true;
}
