#include "PauseState.h"
#include "PlayState.h"
#include "../utils/GameStateMachine.h"
#include <SDL_net.h>
#include "../sdlutils/SDLUtils.h"
#include "../game/ecs_defs.h"



PauseState::PauseState(GameStateMachine* gsm) {
	this->gsm = gsm;
	fightersystem=addSystem<FighterSystem>();
	rendersystem = addSystem<RenderSystem>(0);
	gamecontrolsystem->setstate_(0);

	fightersystem->setContext(this);
	rendersystem->setContext(this);
	gamecontrolsystem->setContext(this);

   
}



//void PauseState::render() {
//	Manager::render();
////	string* t=SDLUtils::instance()->msgs().at("Init");
//	SDL_Color s = { 255,0,0 };
//	//f->renderText("PRESS SPACE TO START", s);
//	f->render(SDLUtils::instance()->renderer(),"PRESS SPACE TO START", (WIN_WIDTH / 2)-60, WIN_HEIGHT / 2, s);
//}

//void PauseState::update() {
//	/*fightersystem->update();
//	rendersystem->update();*/
//
//}
//void PauseState::handleEvents() {
//	SDL_Event event;
//	while (SDL_PollEvent(&event)) {
//		//InputHandler::instance()->update(event);
//		if (event.type==SDL_KEYDOWN)
//		{
//			if (event.key.keysym.sym==SDLK_SPACE) {
//				gsm->popState();
//				if (gsm->empty_stack_()) {
//					gsm->pushState(new PlayState(gsm));
//				}
//			}
//		}
//	}
//}
