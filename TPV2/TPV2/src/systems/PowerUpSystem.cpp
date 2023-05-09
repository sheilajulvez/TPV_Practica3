#include "PowerUpSystem.h"
#include "../ecs/Manager.h"
#include "../components/PowerComponent.h"
PowerUpSystem::PowerUpSystem() {

}
PowerUpSystem::~PowerUpSystem() {

}
void PowerUpSystem::receive(const Message& m) {
	switch (m.id)
	{
	case M_COLLISION_BULLET_ASTEROID:
		newPowerUp(m.asteroid_collision_bullet.a);
		break;
	case M_COLLISION_POWERUP1:
		CollisionPowerUp1(m.f.f);
		break;


	default:
		break;
	}

}
void PowerUpSystem::newPowerUp(Entity* ast) {
	rand = sdlutils().rand().nextInt(0, 2);
	Entity* a = mngr_->addEntity(_grp_POWERUP);
	mngr_->addComponent<Transform>(a, mngr_->getComponent<Transform>(ast)->getPos(), Vector2D{ 0,0 }, P1_W, P1_H);
	if (rand == 0) {	
		mngr_->addComponent<FramedImage>(a, 7, 8, &SDLUtils::instance()->images().at("powerup1"));
		mngr_->addComponent<PowerComponent>(a, true);

	}
	else {
		mngr_->addComponent<FramedImage>(a, 7, 8, &SDLUtils::instance()->images().at("zaragoza"));
		mngr_->addComponent<PowerComponent>(a, false);
	}
		

	

}
void PowerUpSystem::CollisionPowerUp1(Entity* p) {
	mngr_->setAlive(p, false);
}