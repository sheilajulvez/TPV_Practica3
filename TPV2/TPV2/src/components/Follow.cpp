//#include "Follow.h"
//Follow::Follow(Entity* p) {
//	player = p;
//}
// void Follow::initComponent() {
//	 trans = ent_->getComponent<Transform>(_TRANSFORM_H_);
//	 trans_player = player->getComponent<Transform>(_TRANSFORM_H_);
//	 start = sdlutils().currRealTime();
//}
// Follow::~Follow() {
//
//}
//
// void Follow::update() {
//	 totaltime = sdlutils().currRealTime();
//	 frames = totaltime - start;
//	 if (frames > frequency) {
//
//		 start = sdlutils().currRealTime();
//		 trans->setVel(trans->getVel().rotate(trans->getVel().angle(trans_player->getPos() - trans->getPos()) > 0 ? 1.0f : -1.0f));
//
//	 }
//	 
// }