#include "CollisionsSystem.h"
#include "../ecs/Manager.h"
#include "AsteroidsSystem.h"
#include "BulletSystem.h"


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
	
	trans_player = mngr_->getComponent<Transform>(mngr_->getHandler(_HDLR_FIGHTER));
	trans_player2= mngr_->getComponent<Transform>(mngr_->getHandler(_HDLR_NETFIGHTER_2));
	health = mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_FIGHTER));
	health2= mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_NETFIGHTER_2));
	crash = &SDLUtils::instance()->soundEffects().at("explosion");
	bullet_asteroid = &SDLUtils::instance()->soundEffects().at("largewave");
	netsystem = mngr_->getSystem<NETSystem>();
}

// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
// en la práctica 1 y enviar mensajes correspondientes.
void CollisionsSystem::update() {


	if (active_) {
		vector<Entity*> asteroidsgold = mngr_->getEntitiesByGroup(_grp_ASTEROIDS_GOLD);
		vector<Entity*> asteroidsblack = mngr_->getEntitiesByGroup(_grp_ASTEROIDS_BLACK);
		vector<Entity*> bullets = mngr_->getEntitiesByGroup(_grp_BULLET);

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
					health->LessHealth();

				}
				if (Collisions::collidesWithRotation(trans_bullet->getPos(), trans_bullet->getW(), trans_bullet->getH(), trans_bullet->getR(),
					trans_player2->getPos(), trans_player2->getW(), trans_player2->getH(), trans_player2->getR())) {
					Message m;
					bullet_asteroid->play();
					m.id = M_COLLISION_BULLET_ASTEROID;
					m.asteroid_collision_bullet.a = b;
					mngr_->getSystem<BulletsSystem>()->receive(m);
					health2->LessHealth();

				}
			}
			if (Collisions::collidesWithRotation(trans_player->getPos(), trans_player->getW(), trans_player->getH(), trans_player->getR(),
				trans_player2->getPos(), trans_player2->getW(), trans_player2->getH(), trans_player2->getR())) {
				health->LessHealth();
				health2->LessHealth();
			}
		}
		
		else{
			for (auto e : asteroidsgold) {
				trans_asteroid = mngr_->getComponent<Transform>(e);
				if (Collisions::collidesWithRotation(trans_player->getPos(), trans_player->getW(), trans_player->getH(), trans_player->getR(),
					trans_asteroid->getPos(), trans_asteroid->getW(), trans_asteroid->getH(), trans_asteroid->getR()))
				{
					Message m;
					crash->play();
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
						mngr_->getSystem<AsteroidsSystem>()->receive(m);
						bullet_asteroid->play();

					}


				}
			}
			for (auto e : asteroidsblack) {
				trans_asteroid = mngr_->getComponent<Transform>(e);
				if (Collisions::collidesWithRotation(trans_player->getPos(), trans_player->getW(), trans_player->getH(), trans_player->getR(),
					trans_asteroid->getPos(), trans_asteroid->getW(), trans_asteroid->getH(), trans_asteroid->getR()))
				{
					crash->play();
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
						mngr_->getSystem<AsteroidsSystem>()->receive(m);

					}
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
