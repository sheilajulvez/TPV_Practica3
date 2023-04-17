//#include "Gun.h"
//#include "../ecs/Entity.h"
//
//Gun::Gun() {
//	//start= sdlutils().currRealTime();
//}
//Gun::~Gun() {
//
//}
//void Gun::HandleEvent(SDL_Event event) {
//	InputHandler::instance()->update(event);
//	if (InputHandler::instance()->keyDownEvent())
//	{
//		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
//			if (sdlutils().currRealTime()) {
//				if (frames >= 250) {
//					frames = 0;
//					start = sdlutils().currRealTime();
//					shoot = true;
//					fire->play();
//					
//				}
//			}
//		}
//	}
//}
//
//void Gun::initComponent() {
//	trans = ent_->getComponent<Transform>(_TRANSFORM_H_);
//}
//
//void Gun::update() {
//	totaltime = sdlutils().currRealTime();
//	frames = totaltime - start;
//}
