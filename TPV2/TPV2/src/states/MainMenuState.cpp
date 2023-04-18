#include "MainMenuState.h"
#include "PlayState.h"
MainMenuState::MainMenuState(GameStateMachine* gs) {
	g = gs;
}
MainMenuState::~MainMenuState() {

}
void MainMenuState::update() {
	f->render(SDLUtils::instance()->renderer(), "J FOR ONE PLAYER",WIN_WIDTH/4,WIN_HEIGHT/2,c);
	f->render(SDLUtils::instance()->renderer(), "S FOR TWO PLAYER", 3 * WIN_WIDTH / 4, WIN_HEIGHT / 2, c);
	SDL_Event event;
	InputHandler::instance()->update(event);
	if (InputHandler::instance()->keyDownEvent())
	{
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
			g->changeState(new PlayState(g));
		}
		else if(InputHandler::instance()->isKeyDown(SDL_SCANCODE_J)) {
			
		}

	}
}