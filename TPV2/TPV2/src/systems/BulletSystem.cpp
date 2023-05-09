#include "BulletSystem.h"
#include "../ecs/Manager.h"
#include "NETSystem.h"
#include "../components/PowerComponent.h"

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void BulletsSystem::receive(const Message& m) {
	switch (m.id)
	{
	case M_BULLET_SPAWN:
		shoot(m.bullet_spawn.pos, m.bullet_spawn.vel, m.bullet_spawn.width, m.bullet_spawn.height, m.bullet_spawn.rotation);
		break;
	case M_COLLISION_BULLET_ASTEROID:
		onCollision_BulletAsteroid(m.asteroid_collision_bullet.a);
		break;
	case M_ROUND_OVER_:
		onRoundOver();
		break;
	case M_ROUND_START:
		onRoundStart();
		break;
	case M_COLLISION_POWERUP1:
		if (m.f.pepe) {
			power = true;
			max = sdlutils().currRealTime() + 5000;
		}
		break;
	default:
		break;
	}
}
// Inicializar el sistema, etc.
void BulletsSystem::initSystem() {
	netsystem = mngr_->getSystem<NETSystem>();

}
// Si el juego está parado no hacer nada, en otro caso mover las balas y
// desactivar las que salen de la ventana como en la práctica 1.
void BulletsSystem::update() {
	if (active_) {
		for (auto bullet : mngr_->getEntitiesByGroup(_grp_BULLET)) {
			trans = mngr_->getComponent<Transform>(bullet);
			trans->setPos(trans->getPos() + trans->getVel());
			
			if (trans->getPos().getX() + trans->getW() < 0 ||
				trans->getPos().getX() - trans->getW() > WIN_WIDTH ||
				trans->getPos().getY() - trans->getH() > WIN_HEIGHT ||
				trans->getPos().getY() + trans->getH() < 0)
			{
				mngr_->setAlive(bullet, false);
			}
		}
		if (power && sdlutils().currRealTime() > max) {
			power = false;
			max = sdlutils().currRealTime() + 5000;
		}
	}

}
// Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
	// juego, como en la práctica 1. Recuerda que la rotación de la bala sería
	// vel.angle(Vector2D(0.0f,-1.0f))
void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height,double rotation) {
	
	Entity* bullet = mngr_->addEntity(_grp_BULLET);
	trans = mngr_->addComponent<Transform>(bullet, pos, vel, width, height, rotation);

		mngr_->addComponent<PowerComponent>(bullet, power);
	
		
	

	if (netsystem != nullptr) {
		mngr_->getSystem<NETSystem>()->SendBulletSpawn(trans->getPos(), trans->getVel(), trans->getR());
	}
	//mngr_->addComponent<Image>(bullet, t);


}

void BulletsSystem::createBullet(Vector2D pos, Vector2D vel, float r) {
	Entity* bullet = mngr_->addEntity(_grp_BULLET);
	trans = mngr_->addComponent<Transform>(bullet, pos, vel, B_W, B_H, r);
}
// Para gestionar el mensaje de que ha habido un choque entre una bala y un
// asteroide. Desactivar la bala “b”.
void BulletsSystem::onCollision_BulletAsteroid(Entity* b) {
	mngr_->setAlive(b, false);
}
// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
// balas, y desactivar el sistema.
void BulletsSystem::onRoundOver() {
	for (auto bullet : mngr_->getEntitiesByGroup(_grp_BULLET)) {
		mngr_->setAlive(bullet, false);
	}
	active_ = false;
}
// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void BulletsSystem::onRoundStart() {
	active_ = true;

}