#include "WinState.h"
#include "../utils/GameStateMachine.h"
#include "PlayState.h"
#include "PauseState.h"
//void WinState:: render() {
//	Manager::render();
//	f->render(SDLUtils::instance()->renderer(), "YOU WIN", WIN_WIDTH / 2 - 50, WIN_HEIGHT / 3, { 255,0,0 });
//	f->render(SDLUtils::instance()->renderer(), "PRESS SPACE TO CONTINUE", WIN_WIDTH / 2 - 40, WIN_HEIGHT / 2, { 255,0,0 });
//
//}
void WinState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		//InputHandler::instance()->update(event);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_SPACE) {
				gsm->popState();
				if (gsm->empty_stack_()) {
					gsm->pushState(new PauseState(gsm));
				}
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE) {
				gsm->Exit_true();
			}
		}
		
	}
}