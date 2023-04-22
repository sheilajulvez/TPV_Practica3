#include "GameControlSystem.h"
#include "../ecs/Manager.h"
#include "../states/PlayState.h"
#include "../states/PauseState.h"
#include "AsteroidsSystem.h"
#include "../states/WinState.h"
#include "../states/GameOverState.h"


// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
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

// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
// como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
// empieza una ronda o cuando empieza una nueva partida.
void GameCtrlSystem::update() {
	SDL_Event event_;
	InputHandler::instance()->refresh();
 	InputHandler::instance()->update(event_);
	if (InputHandler::instance()->keyDownEvent()) {
			if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
				if (state_ != 1 && mngr_->getSystem<NETSystem>()==nullptr) {				//PAUSA, GAMEOVER, WIN
					
					gsm->popState();
					if (gsm->empty_stack_()) {
						gsm->pushState(new PlayState(gsm));
						Message m;						
						m.id = M_ROUND_START;
						mngr_->send(m);
					}
					
				}
				else if (mngr_->getSystem<NETSystem>() != nullptr) {
					Message m;
					m.id = M_ROUND_START;
					mngr_->send(m);
					mngr_->getSystem<NETSystem>()->SendRoundStart();
					

				}
				else {		//JUEGO
					
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
	// al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
	// es el ganador).
void GameCtrlSystem::onCollision_FighterAsteroid() {

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
// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
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
		/*Message m;
		GameOverState* yi = new GameOverState(gsm);
		gsm->changeState(yi);*/
		/*m.id = M_END;
		m.end.winner = false;
		yi->send(m);*/
		

		if (mngr_->getHandler(_HDLR_FIGHTER) == f && mngr_->getSystem<NETSystem>()->getID()==0) {
			//ha ganadp server, perdido client
			Message m;
			m.id = PLAYER1_WIN;
			mngr_->send(m);

		}
		else if(mngr_->getHandler(_HDLR_NETFIGHTER_2) == f){

		}
		

	}
	else {
		
		Message m;
		m.id = M_PAUSE;
		gsm->currentState()->send(m);
		/*Vector2D pos;
		if (mngr_->getSystem<NETSystem>()->getID()==0) {
			pos = POS1;
		}
		else {
			pos = POS2;
		}
		mngr_->getSystem<FighterSystem>()->SetTrans(mngr_->getSystem<NETSystem>()->getID(), pos, 0);*/

	}
}