//#include "DeAcceleration.h"
//#include "../ecs/Entity.h"
//DeAcceleration::DeAcceleration() {
//
//}
//DeAcceleration:: ~DeAcceleration() {
//}
//void DeAcceleration::initComponent() {
//	trans = ent_->getComponent<Transform>(int(_TRANSFORM_H_));
//
//}
//void DeAcceleration::update() {
//	trans->setVel(trans->getVel() * deacceleration);
//	
//	if (sqrt(pow(trans->getVel().getX(), 2) + pow(trans->getVel().getY(), 2)) < 0.005f) {
//		trans->setVel(Vector2D(0, 0));
//	}
//	
//}