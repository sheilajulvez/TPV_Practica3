#include "NewModeState.h"


NewModeState::NewModeState(GameStateMachine* g) {
	this->gsm = g;

	asteroidsystem = addSystem<AsteroidsSystem>();
	bulletsystem = addSystem<BulletsSystem>();
	fightersystem = addSystem<FighterSystem>();
	powerupsystem = addSystem<PowerUpSystem>();
	collisionsystem = addSystem<CollisionsSystem>();
	rendersystem = addSystem<RenderSystem>(4);
	

	asteroidsystem->setContext(this);
	bulletsystem->setContext(this);
	fightersystem->setContext(this);
	collisionsystem->setContext(this);
	rendersystem->setContext(this);
	gamecontrolsystem->setContext(this);
	powerupsystem->setContext(this);

	gamecontrolsystem->setstate_(4);


	Message m;
	m.id = M_ROUND_START;
	send(m);
}
NewModeState::~NewModeState() {

}
