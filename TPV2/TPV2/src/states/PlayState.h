#pragma once
#include "../ecs/Manager.h"
#include "../utils/GameStateMachine.h"
#include "../systems/FighterSystem.h"
#include "../systems/GameControlSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/AsteroidsSystem.h"
#include "../systems/BulletSystem.h"
#include "../systems/CollisionsSystem.h"

//#include "../game/AsteroidsManager.h"
//#include "../components/FramedImage.h"
//#include "../components/Generations.h"
//#include "../components/DisableOnExit.h"
//#include "../components/Transform.h"
//#include"../components/DeAcceleration.h"
//#include "../components/Image.h"
//#include "../components/Health.h"
//#include "../components/FighterCtrl.h"
//#include"../components/Gun.h"
//#include "../components/ShowAtOpposideSide.h"

#include "../utils/checkML.h"
class PlayState : public Manager 
{

	public:
	PlayState(GameStateMachine* gsm) ;
	virtual ~PlayState() { //delete(asteroidmanager); 
	}
		//void update();
		void handleEvents();
		void checkCollisison();
		void Reset();

	private:

	/*FighterCtrl* control;
	Gun* gun;*/

	GameStateMachine* gsm;
	AsteroidsSystem* asteroidsystem;
	BulletsSystem* bulletsystem;
	CollisionsSystem* collisionsystem;
	FighterSystem* fightersystem;
	RenderSystem* rendersystem;





	/*AsteroidsManager* asteroidmanager;
	Transform* trans_asteroid;
	Transform* trans_bullet;
	SoundEffect* explosion=&SDLUtils::instance()->soundEffects().at("explosion");
	SoundEffect* crash=&SDLUtils::instance()->soundEffects().at("largewave");*/

};