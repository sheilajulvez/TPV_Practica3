#include "Manager.h"
#include "../utils/GameStateMachine.h"


Manager::Manager() {
	
	for (auto& grpEnts : entsByGroup_) {
		grpEnts.reserve(100);
	}
	
	for (int i = 0; i < maxSystemId; ++i) {
		sys_[i] = nullptr;
	}
	
	gamecontrolsystem = addSystem<GameCtrlSystem>(GameStateMachine::instance());
	gamecontrolsystem->initSystem();
	gamecontrolsystem->setContext(this);

	/*fighter = addEntity(_grp_GENERAL);
	

	t_fighter = &SDLUtils::instance()->images().at("fighter");
	trans_player = fighter->addComponent<Transform>(int(_TRANSFORM_H_), F_position, F_velocity, F_Width, F_Heigth);
	assert(trans_player != nullptr);
	fighter->addComponent<Image>(_IMAGE_H, t_fighter);
	
	health = fighter->addComponent<Health>(_HEALTH_H);*/

}


Manager::~Manager() {
	for (auto& ents : entsByGroup_) {
		for (auto e : ents)
			delete e;
	}
}


void Manager::refresh() {
	for (grpId_type gId = 0; gId < maxGroupId; gId++) {
		auto& grpEnts = entsByGroup_[gId];
		grpEnts.erase(
			std::remove_if(grpEnts.begin(), grpEnts.end(),
				[](Entity* e) {
					if (e->alive_) {
						return false;
					}
					else {
						delete e;
						return true;
					}
				}),
			grpEnts.end());
	}
}

void Manager::update() {
	for (auto& s: sys_) {
		if (s != nullptr) {
			s->update();
		}
			
	}
}
inline bool Manager::isAlive(Entity* e) {
	return e->alive_;
}




	

