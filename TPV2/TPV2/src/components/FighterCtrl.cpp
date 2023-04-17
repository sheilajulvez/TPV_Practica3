#include "FighterCtrl.h"
#include "../ecs/Entity.h"

FighterCtrl::FighterCtrl() {


}
FighterCtrl::~FighterCtrl() {

}
void FighterCtrl::initComponent() {
	//trans=mngr_->getComponent<Transform>(ent_);
}
void FighterCtrl::HandleEvent(SDL_Event event) {
	InputHandler::instance()->update(event);
	if (InputHandler::instance()->keyDownEvent())
	{

		if(InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT)){
		
			trans->setR(trans->getR()+ 5);
			//trans->RotationVector();
			
		}
		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
			trans->setR(trans->getR() - 5);
			//trans->RotationVector();

		}
		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_UP)) {

			//trans->setVel(trans->getVel() + (Vector2D(0,-1).rotate(trans->getR())*acceleration));
			
			if (sqrt(pow(trans->getVel().getX(), 2) + pow(trans->getVel().getY(), 2)) < 4) {
			trans->setVel(trans->getVel() + (Vector2D(0, -1).rotate(trans->getR()) * acceleration));
			}
			else {
			trans->setVel(trans->getVel().normalize() * 4);
			}
				
		}
		
	}	

}