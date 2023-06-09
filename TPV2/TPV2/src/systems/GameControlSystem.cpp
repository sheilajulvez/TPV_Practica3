#include "GameControlSystem.h"
#include "../ecs/Manager.h"
#include "../states/PlayState.h"
#include "../states/PauseState.h"
#include "AsteroidsSystem.h"
#include "../states/WinState.h"
#include "../states/GameOverState.h"


// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
void GameCtrlSystem::receive(const Message& m)  {
	switch (m.id) {
	case M_COLLISION_FIGHTER_ASTEROID:
		onCollision_FighterAsteroid();
		break;

	case M_ASTEROIDS_EXTINCTION:
		onAsteroidsExtinction();
		break;
	case M_COLLISION_FIGHTER:
		CollisionFighter(m.f.f);
		break;
	default: break;
	}
}


// Inicializar el sistema, etc.
void GameCtrlSystem::initSystem() {
	state_ = 0;
}

// Si el juego no est� parado y el jugador pulsa SDLK_SPACE cambia el estado
// como en la pr�ctica 1, etc. Tiene que enviar mensajes correspondientes cuando
// empieza una ronda o cuando empieza una nueva partida.
void GameCtrlSystem::update() {
	SDL_Event event_;
	InputHandler::instance()->refresh();
 	InputHandler::instance()->update(event_);
	if (InputHandler::instance()->keyDownEvent()) {
			if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {

				//PAUSA, GAMEOVER, WIN
				if (state_ != 1 && mngr_->getSystem<NETSystem>()==nullptr) {				
					
					gsm->popState();
					if (gsm->empty_stack_()) {
						gsm->pushState(new PlayState(gsm));
						Message m;						
						m.id = M_ROUND_START;
						mngr_->send(m);
					}
					
				}
				//MULTIPLAYER
				else if (mngr_->getSystem<NETSystem>() != nullptr) {		
					Message m;
					m.id = M_ROUND_START;
					mngr_->send(m);
					mngr_->getSystem<NETSystem>()->SendRoundStart();
					

				}
				//JUEGO
				else {		
					PauseState* p = new PauseState(gsm);
					gsm->pushState(p);
					p->getComponent<Health>(p->getHandler(_HDLR_FIGHTER))->setHealth(mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_FIGHTER))->GetHealth());
					Message m;
					m.id = M_PAUSE;
					p->send(m);
				}		
			}
		
	}


}

// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay m�s vidas avisar que ha acabado el juego (y quien
	// es el ganador).
void GameCtrlSystem::onCollision_FighterAsteroid() {


	if (!mngr_->getSystem<FighterSystem>()->getvidainfinita()) {
		Message m;
		m.id = M_ROUND_OVER_;
		mngr_->getSystem<AsteroidsSystem>()->receive(m);

		m.id = M_ROUND_START;
		mngr_->send(m);
		mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_FIGHTER))->LessHealth();
		if (mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_FIGHTER))->GetHealth() < 1) {
			Message m;
			GameOverState* yi = new GameOverState(gsm);
			gsm->changeState(yi);
			m.id = M_END;
			m.end.winner = false;
			yi->send(m);

		}
		else {
			PauseState* p = new PauseState(gsm);
			gsm->pushState(p);
			p->getComponent<Health>(p->getHandler(_HDLR_FIGHTER))->setHealth(mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_FIGHTER))->GetHealth());
			Message m;
			m.id = M_PAUSE;
			p->send(m);

		}
	}
	


}
// Para gestionar el mensaje de que no hay m�s asteroides. Tiene que avisar que
// ha acabado la ronda y adem�s que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {
	Message m;
	m.id = M_ROUND_OVER_;
	mngr_->send(m);
	WinState* yi = new WinState(gsm);
	gsm->changeState(yi);
	m.id = M_END;
	m.end.winner = true;
	yi->send(m);
}


void GameCtrlSystem::CollisionFighter(Entity* f) {
	Message m;
	m.id = M_ROUND_START;
	mngr_->send(m);
	mngr_->getComponent<Health>(f)->LessHealth();

	if (mngr_->getComponent<Health>(f)->GetHealth() < 1) {
		if (mngr_->getSystem<NETSystem>() == nullptr) {
			Message m;
			GameOverState* yi = new GameOverState(gsm);
			gsm->changeState(yi);
			m.id = M_END;
			m.end.winner = false;
			yi->send(m);

		}
		
		else {
			if (mngr_->getHandler(_HDLR_FIGHTER) == f  ) {
				if (mngr_->getSystem<NETSystem>()->getID() == 0) {
					Message m;
					m.id = PLAYER1_WIN;
					mngr_->send(m);
					mngr_->getSystem<RenderSystem>()->setText("YOU LOOSE");

				}
				else {
					Message m;
					m.id = PLAYER1_WIN;
					mngr_->send(m);
					mngr_->getSystem<RenderSystem>()->setText("YOU WIN");
				}
				
				
				

				//mngr_->getSystem<NETSystem>()->PlayersWin(mngr_->getSystem<NETSystem>()->get_MyName() + " HAS LOST");

			}
			else if (mngr_->getHandler(_HDLR_NETFIGHTER_2) == f ) {

				if (mngr_->getSystem<NETSystem>()->getID() == 1) {
					Message m;
					m.id = PLAYER1_WIN;
					mngr_->send(m);
					mngr_->getSystem<RenderSystem>()->setText("YOU LOOSE");

				}
				else {
					Message m;
					m.id = PLAYER1_WIN;
					mngr_->send(m);
					mngr_->getSystem<RenderSystem>()->setText("YOU WIN");
				}
				/*Message m;
				m.id = PLAYER2_WIN;
				mngr_->send(m);

				mngr_->getSystem<RenderSystem>()->setText(mngr_->getSystem<NETSystem>()->get_otherName() + " HAS LOST");*/

				//mngr_->getSystem<NETSystem>()->PlayersWin(mngr_->getSystem<NETSystem>()->get_MyName() + " HAS WIN");

			}
		}
		

	}
	else {
		
		Message m;
		m.id = M_PAUSE;
		gsm->currentState()->send(m);
		

	}
}