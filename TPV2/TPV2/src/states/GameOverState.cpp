#include "GameOverState.h"
#include "../utils/GameStateMachine.h"
#include "PauseState.h"

GameOverState::GameOverState(GameStateMachine* gsm) {
	this->gsm = gsm;
	f = &SDLUtils::instance()->fonts().at("ARIAL16");
	render = addSystem<RenderSystem>(2);
	render->setContext(this);
	gamecontrolsystem->setContext(this);
	gamecontrolsystem->setstate_(2);
	fighter = addSystem<FighterSystem>();
}
//void GameOverState::render() {
//	Manager::render();
//	f->render(SDLUtils::instance()->renderer(), "YOU LOOSE", WIN_WIDTH / 2 - 50, WIN_HEIGHT / 3, { 255,0,0 });
//	f->render(SDLUtils::instance()->renderer(), "PRESS SPACE TO CONTINUE", WIN_WIDTH / 2 - 40, WIN_HEIGHT / 2, { 255,0,0 });
//
//}
void GameOverState::handleEvents() {
	SDL_Event event;
	/*while (SDL_PollEvent(&event)) {
		InputHandler::instance()->update(event);
		if (InputHandler::instance()->keyDownEvent())
		{
			if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
				
				gsm->changeState(new PauseState(gsm));
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE) {
				gsm->Exit_true();
			}
		}
		
	}*/
}


