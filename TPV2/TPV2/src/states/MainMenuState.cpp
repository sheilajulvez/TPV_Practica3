#include "MainMenuState.h"
#include "PlayState.h"
#include "MultiPlayerState.h"
#include "PauseState.h"
#include "NewModeState.h"
MainMenuState::MainMenuState(GameStateMachine* gs) {
	g = gs;
}
MainMenuState::~MainMenuState() {
}
void MainMenuState::update() {
	SDL_Color c = { 255,0,0 };
	f->render(SDLUtils::instance()->renderer(), "J FOR ONE PLAYER", WIN_WIDTH / 5, WIN_HEIGHT / 2, c);
	f->render(SDLUtils::instance()->renderer(), "S FOR TWO PLAYER",  2* WIN_WIDTH / 5+10, WIN_HEIGHT / 2, c);
	f->render(SDLUtils::instance()->renderer(), "V FOR NEW MODE", 3 * WIN_WIDTH / 5+10, WIN_HEIGHT / 2, c);
	SDL_RenderPresent(SDLUtils::instance()->renderer());
	SDL_Delay(500);

	SDL_Event event_;
	//InputHandler::instance()->update(event_);
	InputHandler::instance()->refresh();

	if (InputHandler::instance()->keyDownEvent()) {
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
			g->pushState(new MultiPlayerState(g));
		}
		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_J)) {
			g->pushState(new PlayState(g));
			g->pushState(new PauseState(g));
		}
		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_V)) {
			g->pushState(new NewModeState(g));
			g->pushState(new PauseState(g));
		}
	}
	
}
