#include "PlayState.h"
#include "../utils/Collisions.h"
#include "../states/PauseState.h"
#include "../states/WinState.h"
#include "../states/GameOverState.h"
#include "WinState.h"

 PlayState::PlayState(GameStateMachine* gsm) {
	 this->gsm = gsm;
	 /*asteroidmanager = new AsteroidsManager(this,fighter);
	 asteroidmanager->createAsteroids(10);

	 fighter->addComponent<DeAcceleration>(_DEACELERATION_H_);
	 control = fighter->addComponent<FighterCtrl>(_FIGHTERCTRL_H);
	 gun = fighter->addComponent<Gun>(_GUN_H);
	 fighter->addComponent<ShowAtOpposideSide>(_OPPOSITE_H);

	 assert(control != nullptr);
	 assert(gun != nullptr);*/
	 asteroidsystem = addSystem<AsteroidsSystem>();
	 bulletsystem = addSystem<BulletsSystem>();
	 
	 fightersystem = addSystem<FighterSystem>();
	 collisionsystem = addSystem<CollisionsSystem>();
	 rendersystem = addSystem<RenderSystem>(1);


	 asteroidsystem->setContext(this);
	 bulletsystem->setContext(this);
	 fightersystem->setContext(this);
	 collisionsystem->setContext(this);
	 rendersystem->setContext(this);
	 gamecontrolsystem->setContext(this);


	 
	 gamecontrolsystem->setstate_(1);
	 Message m;
	 m.id = M_ROUND_START;
	 send(m);

	
 }
//void PlayState::update() {
	//Manager::update();
	////asteroidmanager->addAsteroidFrequently();

	//if (gun->getshot()) {
	//	gun->setshot();
	//	Entity* bullet = addEntity(_grp_BULLET);
	//	Texture* t = &SDLUtils::instance()->images().at("bullet");

	//	Vector2D bPos = trans_player->getPos()
	//		+ Vector2D(trans_player->getW() / 2.0f, trans_player->getH() / 2.0f)
	//		- Vector2D(0.0f, trans_player->getH() / 2.0f + 5.0f + 12.0f).rotate(trans_player->getR())
	//		- Vector2D(2.0f, 10.0f);
	//	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(trans_player->getR()) * (trans_player->getVel().magnitude() + 5.0f);
	//	float w = 5;
	//	float h = 20;
	//	float r = trans_player->getR();
	//	mngr_->addComponent<Transform>(bullet, bPos, bVel, w, h, r);
	//	//bullet->addComponent<Image>(_IMAGE_H, t);
	//	

	//	
	//}
	//checkCollisison();
//}
void PlayState::handleEvents() {
	
}

void PlayState::Reset() {
	/*asteroidmanager->createAsteroids(10);
	vector<Entity*> asteroids = getEntitiesbyGroup(_grp_ASTEROIDS);
	for (auto e : asteroids) {
		trans_asteroid = e->getComponent<Transform>(_TRANSFORM_H_);
		if (Collisions::collidesWithRotation(trans_player->getPos(), trans_player->getW(), trans_player->getH(), trans_player->getR(),
			trans_asteroid->getPos(), trans_asteroid->getW(), trans_asteroid->getH(), trans_asteroid->getR()))
		{
			trans_player->setPos({ WIN_WIDTH / 2, WIN_HEIGHT / 2 });
			trans_player->setVel({ 0,0 });
			trans_player->setR(0);
			return;
		}
	}*/
	//trans_player->setPos({ WIN_WIDTH / 2, WIN_HEIGHT / 2 });
	//trans_player->setVel({ 0,0 });
	//trans_player->setR(0);
}
void PlayState::checkCollisison() {
	//vector<Entity*> asteroids = getEntitiesbyGroup(_grp_ASTEROIDS);
	//vector<Entity*> bullets = getEntitiesbyGroup(_grp_BULLET);
	//for (auto e : asteroids) {
	//	trans_asteroid = e->getComponent<Transform>(_TRANSFORM_H_);
	//	if (Collisions::collidesWithRotation(trans_player->getPos(), trans_player->getW(), trans_player->getH(), trans_player->getR(),
	//		trans_asteroid->getPos(), trans_asteroid->getW(), trans_asteroid->getH(), trans_asteroid->getR()))
	//	{
	//		asteroidmanager->destroyAllAsteroids();
	//		crash->play();
	//		for (auto b : bullets)b->setAlive(false);
	//		health->LessHealth();

	//		if (health->GetHealth() < 1) {
	//			gsm->changeState(new GameOverState(gsm));
	//		}
	//		else {
	//			/*asteroidmanager->createAsteroids(10);
	//			trans_player->setPos({ WIN_WIDTH / 2, WIN_HEIGHT / 2 });
	//			trans_player->setVel({ 0,0 });
	//			trans_player->setR(0);*/
	//			PauseState* s = new PauseState(gsm);
	//			gsm->pushState(s);
	//			int n = health->GetHealth();
	//			s->setLifes(n);
	//			//gsm->pushState(new PauseState(gsm));
	//		}
	//	}
	//	for (auto b : bullets) {
	//		trans_bullet = b->getComponent<Transform>(_TRANSFORM_H_);
	//		if (Collisions::collidesWithRotation(trans_bullet->getPos(), trans_bullet->getW(), trans_bullet->getH(), trans_bullet->getR(),
	//			trans_asteroid->getPos(), trans_asteroid->getW(), trans_asteroid->getH(), trans_asteroid->getR())) {
	//			b->setAlive(false);
	//			asteroidmanager->onCollision(e);
	//			explosion->play();
	//			if (asteroidmanager->getN_asteroids() <= 0) {
	//				//WIN
	//				gsm->changeState(new WinState(gsm));
	//			}
	//		}
	//	}
	//}
}
