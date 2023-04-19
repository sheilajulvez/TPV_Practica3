#include "AsteroidsSystem.h"
#include "../ecs/Manager.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void AsteroidsSystem :: receive(const Message& m) {
	switch (m.id)
	{
	case M_COLLISION_BULLET_ASTEROID:
		onCollision_AsteroidBullet(m.asteroid_collision_bullet.a);
		break;
	case M_ROUND_OVER_:
		onRoundOver(); 
		break;
	case M_ROUND_START:
		onRoundStart();
		break;
	default:
		break;
	}

}
// Inicializar el sistema, etc.
void AsteroidsSystem::initSystem() {
	random = &SDLUtils::instance()->rand();
	start_t = SDLUtils::instance()->currRealTime();
}
// Si el juego está parado no hacer nada, en otro caso mover los asteroides como
// en la práctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
// de los 10 al principio de cada ronda).
void AsteroidsSystem::update() {


		//que aparezca 1 cada cierto tiempo
		int totaltime = sdlutils().currRealTime();
		framed_time = totaltime - start_t;
		if (framed_time > frequency) {
			createAsteroids(1);
			framed_time = 0;
			start_t = totaltime;
		}

		//Follow
		for (auto enemy : mngr_->getEntitiesByGroup(_grp_ASTEROIDS_GOLD)) {
			Transform* trans = mngr_->getComponent<Transform>(enemy);

			
			frames = sdlutils().currRealTime(); - start_t;
		
				start_t = sdlutils().currRealTime();
				trans->setVel(trans->getVel().rotate(trans->getVel().angle(mngr_->getComponent<Transform>(mngr_->getHandler(_HDLR_FIGHTER))->getPos()
				- trans->getPos()) > 0 ? 1.0f : -1.0f));
			
			trans->setPos(trans->getPos() + trans->getVel());
		}

		//ShowOppositeSide
		for (auto enemy : mngr_->getEntitiesByGroup(_grp_ASTEROIDS_BLACK)) {
			Transform* trans = mngr_->getComponent<Transform>(enemy);
			if (trans->getPos().getX() > (WIN_WIDTH + trans->getW())) {
				trans->setPos({ 0,trans->getPos().getY() });
			}
			else if (trans->getPos().getX() + trans->getW() < 0) {
				trans->setPos({ WIN_WIDTH,trans->getPos().getY() });

			}
			if (trans->getPos().getY() > (WIN_HEIGHT + trans->getH())) {
				trans->setPos({ trans->getPos().getX(), 0 });
			}
			else if (trans->getPos().getY() + trans->getH() < 0) {
				trans->setPos({ trans->getPos().getX(), WIN_HEIGHT });
			}
			trans->setPos(trans->getPos() + trans->getVel());
		}	
	
}


// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1,
	// y si no hay más asteroides enviar un mensaje correspondiente.
void AsteroidsSystem::onCollision_AsteroidBullet(Entity* a) {

	mngr_->setAlive(a, false);
	int size = mngr_->getComponent<Generations>(a)->getState();
	Transform* t = mngr_->getComponent<Transform>(a);
	if ((size == 3 || size == 2) && numOfAsteroids_ < 30) {
		createone(t->getW(), t->getH(), size - 1, a);
		if (numOfAsteroids_ < 29) {
			createone(t->getW(), t->getH(), size - 1, a);
		}

	}
	numOfAsteroids_--;
	
	if (numOfAsteroids_ < 1) {
		Message m;
		m.id = M_ASTEROIDS_EXTINCTION;
		m.end.winner = true;		//gana el player
		mngr_->send(m);
	}

}

void  AsteroidsSystem::createone(int w, int h, int size, Entity* father) {
	Entity* asteroid;
	Texture* t_asteroid;
	if (sdlutils().rand().nextInt(0, 10) < 3) {
		asteroid = mngr_->addEntity(_grp_ASTEROIDS_GOLD);
		t_asteroid = &SDLUtils::instance()->images().at("asteroid_gold");
		//mngr_->addComponent<Follow>(asteroid, mngr_->getSystem<FighterCtrl>());		

	}
	else {
		asteroid = mngr_->addEntity(_grp_ASTEROIDS_BLACK);
		t_asteroid = &SDLUtils::instance()->images().at("asteroid");
	}

	//position y velocity
	auto r = sdlutils().rand().nextInt(0, 360);
	Vector2D pos = mngr_->getComponent<Transform>(father)->getPos() + mngr_->getComponent<Transform>(father)->getVel().rotate(r) * 2 * max(w, h);
	Vector2D vel = mngr_->getComponent<Transform>(father)->getVel().rotate(r) * 1.1f;
	int width = 10.0f + 5.0f * size;
	int height = 10.0f + 5.0f * size;

	mngr_->addComponent<Transform>(asteroid, pos, vel, width, height);
	mngr_->addComponent<Generations>(asteroid, size);
	mngr_->addComponent<FramedImage>(asteroid, A_fils, A_cols, t_asteroid);
	numOfAsteroids_++;

}
// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
// asteroides, y desactivar el sistema.
void AsteroidsSystem::onRoundOver() {
	
	vector<Entity*> ent = mngr_->getEntitiesByGroup(_grp_ASTEROIDS_GOLD);
	for (auto a : ent) {
		mngr_->setAlive(a,false);
	}
	ent = mngr_->getEntitiesByGroup(_grp_ASTEROIDS_BLACK);
	for (auto a : ent) {
		mngr_->setAlive(a, false);
	}
	
	numOfAsteroids_ = 0;
	active_ = false;

}
// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
// añadir los asteroides iniciales (como en la práctica 1).
void AsteroidsSystem::onRoundStart() {
	active_ = true;
	createAsteroids(10);
}
void AsteroidsSystem::createAsteroids(int n) {
	for (int i = 0; i < n; ++i) {
		
		Texture* t_asteroid;
		Entity* asteroid;

		if (sdlutils().rand().nextInt(0, 10) < 3) {
			t_asteroid = &SDLUtils::instance()->images().at("asteroid_gold");
			asteroid = mngr_->addEntity(_grp_ASTEROIDS_GOLD);
		
		}
		else {
			t_asteroid = &SDLUtils::instance()->images().at("asteroid");
			asteroid = mngr_->addEntity(_grp_ASTEROIDS_BLACK);
		}

		//position
		int where = random->nextInt(0, 4);
		float pos_x = random->nextInt(0, WIN_WIDTH);
		float pos_y = random->nextInt(0, WIN_HEIGHT);
		if (where == 0) {//abajo
			pos_x = random->nextInt(0, WIN_WIDTH);
			pos_y = random->nextInt(WIN_HEIGHT - 10, WIN_WIDTH);

		}
		else if (where == 1) {//arriba
			pos_x = random->nextInt(0, WIN_WIDTH);
			pos_y = random->nextInt(-5, 20);
		}
		else if (where == 2) {//izq
			pos_x = random->nextInt(-10, 20);
			pos_y = random->nextInt(0, WIN_HEIGHT);
		}
		else {//derecha
			pos_x = random->nextInt(WIN_WIDTH - 20, WIN_WIDTH + 5);
			pos_y = random->nextInt(0, WIN_HEIGHT);
		}
		Vector2D pos = { pos_x,pos_y };

		//velocity
		Vector2D v{ WIN_WIDTH / 2, WIN_HEIGHT / 2 };
		Vector2D x{ (float)random->nextInt(-100,101),(float)random->nextInt(-100,101) };
		float speed = sdlutils().rand().nextInt(-10, 10) / 10.0f;
		Vector2D velocity = (v - x).normalize() * speed;

		//tamaño
		int r = random->nextInt(1, 4);
		float wi = 10.0f + 5.0f * r;
		float he = 10.0f + 5.0f * r;

		mngr_->addComponent<Transform>(asteroid, pos, velocity, wi, he);
		mngr_->addComponent<Generations>(asteroid, r);
		mngr_->addComponent<FramedImage>(asteroid, A_fils, A_cols, t_asteroid);

		numOfAsteroids_++;
	}
}