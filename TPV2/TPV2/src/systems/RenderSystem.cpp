#include "RenderSystem.h"
#include "../ecs/Manager.h"
#include "NETSystem.h"



RenderSystem::RenderSystem(int s) {
	state_ = s;
}
// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
void RenderSystem::receive(const Message& m) {
	switch (m.id) {
	case M_PAUSE:
		state_ = 0;
		break;
	case M_END:
		onGameOver(m.end.winner);
		break;
	case M_START:
		onGameStart();
		break;
	case M_ROUND_OVER_:
		onRoundOver();
		break;
	case M_ROUND_START:
		onRoundStart();
		break;
	case PLAYER1_WIN:
		if (mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_FIGHTER))->GetHealth() < 1 || 
			mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_NETFIGHTER_2))->GetHealth() < 1) {
			state_ = 3;
		}
		break;
	case PLAYER2_WIN:
		if (mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_NETFIGHTER_2))->GetHealth() < 1) {
			state_ = 3;
		}
		break;
	}
}
// Inicializar el sistema, etc.
void RenderSystem::initSystem() {
	f = &SDLUtils::instance()->fonts().at("ARIAL16");
	fighter_texture = &SDLUtils::instance()->images().at("fighter");
	health_texture = &SDLUtils::instance()->images().at("health");
	renderer = SDLUtils::instance()->renderer();
	black_asteroids=&SDLUtils::instance()->images().at("asteroid");
	gold_asteroids = &SDLUtils::instance()->images().at("asteroid_gold");
	bullet_texture = &SDLUtils::instance()->images().at("bullet");
	tpowerup1 = &SDLUtils::instance()->images().at("powerup1");
}


// - Dibujar los mensajes correspondientes: si el juego est� parado, etc (como en
// la pr�ctica 1)
void RenderSystem::update() {
	//Pause=0, Play=1, Win=2, GameOver=3
	SDL_RenderClear(renderer);
	trans= mngr_->getComponent<Transform>(mngr_->getHandler(_HDLR_FIGHTER));

	dest.x = trans->getPos().getX();
	dest.y = trans->getPos().getY();
	dest.w = trans->getW();		
	dest.h = trans->getH();
	fighter_texture->render(dest, trans->getR());

	n_health = mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_FIGHTER))->GetHealth();
	// - Dibujar las vidas (siempre).
	for (int i = 0; i < n_health; ++i) {
		health.x = i * (HEALTH_W + HEALTH_X);
		health.y = HEALTH_Y;
		health.w = HEALTH_W;
		health.h = HEALTH_H;
		health_texture->render(health,0);
	}


	//multiplayer
	if (mngr_->getSystem<NETSystem>() != nullptr) {
		SDL_Color c = { 255,0,0 };
		if (mngr_->getSystem<NETSystem>()->getID() == 0) {
			 name = mngr_->getSystem<NETSystem>()->get_MyName();
			 other = mngr_->getSystem<NETSystem>()->get_otherName();
		}
		else {
			other = mngr_->getSystem<NETSystem>()->get_MyName();
			name = mngr_->getSystem<NETSystem>()->get_otherName();
		}		
		f->render(SDLUtils::instance()->renderer(),name ,trans->getPos().getX(), trans->getPos().getY() + trans->getH()+5, c);
		
		 //if (name == "")name = "Client";
		trans = mngr_->getComponent<Transform>(mngr_->getHandler(_HDLR_NETFIGHTER_2));
		f->render(SDLUtils::instance()->renderer(), other, trans->getPos().getX(),trans->getPos().getY() + trans->getH() + 5, c);

		dest.x = trans->getPos().getX();
		dest.y = trans->getPos().getY();
		dest.w = trans->getW();
		dest.h = trans->getH();
		fighter_texture->render(dest, trans->getR());

		n_health = mngr_->getComponent<Health>(mngr_->getHandler(_HDLR_NETFIGHTER_2))->GetHealth();
		for (int i = 0; i < n_health; ++i) {
			health.x = i * (HEALTH_W + HEALTH_X) + 600;
			health.y = HEALTH_Y;
			health.w = HEALTH_W;
			health.h = HEALTH_H;
			health_texture->render(health, 0);
		}

	}
	

	//PLAYSTATE
	if (state_ == 1) {	
		// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
		vector<Entity*> astd_black = mngr_->getEntitiesByGroup(_grp_ASTEROIDS_BLACK);
		vector<Entity*> astd_gold = mngr_->getEntitiesByGroup(_grp_ASTEROIDS_GOLD);
		vector<Entity*> bullet = mngr_->getEntitiesByGroup(_grp_BULLET);
		for (auto c : astd_black) {
			Transform* astd_b = mngr_->getComponent<Transform>(c);
			FramedImage* f = mngr_->getComponent<FramedImage>(c);
			int cont = f->getCont();
			int cont2 = f->getCont2();
			int i = f->getI();
			cont++;
			if (cont >= 5) {
				i++;
				cont = 0;
			}
			if (i == AST_F) {
				cont2++;
				cont2 %= AST_C;
				i = 0;
			}
			i = i % AST_F;
			f->setCont(cont);
			f->setCont2(cont2);
			f->setI(i);
			SDL_Rect dest, src;
			dest.x = astd_b->getPos().getX();
			dest.y = astd_b->getPos().getY();
			dest.w = astd_b->getW();		//mirar
			dest.h = astd_b->getH();
			src.x = i * (510 / AST_F);
			src.y = cont2 * (500 / AST_C);
			src.w = 510 / AST_F;
			src.h = 500 / AST_C;
			black_asteroids->render(src, dest);

		}
		for (auto gold : astd_gold) {
			Transform* astd_g = mngr_->getComponent<Transform>(gold);
		
			FramedImage* f = mngr_->getComponent<FramedImage>(gold);
			int cont = f->getCont();
			int cont2 = f->getCont2();
			int i = f->getI();

			cont++;
			if (cont >= 5) {
				i++;
				cont = 0;
			}
			if (i == AST_F) {
				cont2++;
				cont2 %= AST_C;
				i = 0;
			}
			i = i % AST_F;
			f->setCont(cont);
			f->setCont2(cont2);
			f->setI(i);
			
			SDL_Rect dest, src;
			dest.x = astd_g->getPos().getX();
			dest.y = astd_g->getPos().getY();
			dest.w = astd_g->getW();		//mirar
			dest.h = astd_g->getH();
			src.x = i * (510 / AST_F);
			src.y = cont2 * (500 / AST_C);
			src.w = 510 / AST_F;
			src.h = 500 / AST_C;
			gold_asteroids->render(src, dest);
		}

		for (auto b : bullet) {
		
				Transform* transb = mngr_->getComponent<Transform>(b);
				SDL_Rect dest;
				dest.x = transb->getPos().getX();
				dest.y = transb->getPos().getY();
				dest.w = transb->getW();
				dest.h = transb->getH();
				bullet_texture->render(dest, transb->getR());
			
			
		}

	}
	//PAUSE STATE
	else if (state_ == 0) {	
		
		SDL_Color s = { 255,0,0 };
		f->renderText("PRESS SPACE TO START", s);
		f->render(SDLUtils::instance()->renderer(),"PRESS SPACE TO START", (WIN_WIDTH / 2)-60, WIN_HEIGHT / 2, s);

	}
	//ENDSTATE
	else if (state_ == 2) {
		// 0 - None, 1 - Asteroid, 2- Fighter
		if (winner_ == 1){
			f->render(SDLUtils::instance()->renderer(), "YOU LOOSE", WIN_WIDTH / 2 - 50, WIN_HEIGHT / 3, { 255,0,0 });
			f->render(SDLUtils::instance()->renderer(), "PRESS SPACE TO CONTINUE", WIN_WIDTH / 2 - 40, WIN_HEIGHT / 2, { 255,0,0 });
			
		}
		else if (winner_ == 2) {
			f->render(SDLUtils::instance()->renderer(), "YOU WIN", WIN_WIDTH / 2 - 50, WIN_HEIGHT / 3, { 255,0,0 });
			
			f->render(SDLUtils::instance()->renderer(), "PRESS SPACE TO CONTINUE", WIN_WIDTH / 2 - 40, WIN_HEIGHT / 2, { 255,0,0 });
		}
	

	}
	//MULTIPLAYER ENDSTATE
	else if (state_ == 3) {
		SDL_Color s = { 255,0,0 };
		f->renderText(text, s);
		f->render(SDLUtils::instance()->renderer(), text, (WIN_WIDTH / 2) - 60, WIN_HEIGHT / 2, s);
	}
	else if (state_ == 4) {
		// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
		vector<Entity*> astd_black = mngr_->getEntitiesByGroup(_grp_ASTEROIDS_BLACK);
		vector<Entity*> astd_gold = mngr_->getEntitiesByGroup(_grp_ASTEROIDS_GOLD);
		vector<Entity*> bullet = mngr_->getEntitiesByGroup(_grp_BULLET);
		vector<Entity*> powerup1 = mngr_->getEntitiesByGroup(_grp_POWERUP);
		for (auto c : astd_black) {
			Transform* astd_b = mngr_->getComponent<Transform>(c);
			FramedImage* f = mngr_->getComponent<FramedImage>(c);
			int cont = f->getCont();
			int cont2 = f->getCont2();
			int i = f->getI();
			cont++;
			if (cont >= 5) {
				i++;
				cont = 0;
			}
			if (i == AST_F) {
				cont2++;
				cont2 %= AST_C;
				i = 0;
			}
			i = i % AST_F;
			f->setCont(cont);
			f->setCont2(cont2);
			f->setI(i);
			SDL_Rect dest, src;
			dest.x = astd_b->getPos().getX();
			dest.y = astd_b->getPos().getY();
			dest.w = astd_b->getW();		//mirar
			dest.h = astd_b->getH();
			src.x = i * (510 / AST_F);
			src.y = cont2 * (500 / AST_C);
			src.w = 510 / AST_F;
			src.h = 500 / AST_C;
			black_asteroids->render(src, dest);

		}
		for (auto gold : astd_gold) {
			Transform* astd_g = mngr_->getComponent<Transform>(gold);

			FramedImage* f = mngr_->getComponent<FramedImage>(gold);
			int cont = f->getCont();
			int cont2 = f->getCont2();
			int i = f->getI();

			cont++;
			if (cont >= 5) {
				i++;
				cont = 0;
			}
			if (i == AST_F) {
				cont2++;
				cont2 %= AST_C;
				i = 0;
			}
			i = i % AST_F;
			f->setCont(cont);
			f->setCont2(cont2);
			f->setI(i);

			SDL_Rect dest, src;
			dest.x = astd_g->getPos().getX();
			dest.y = astd_g->getPos().getY();
			dest.w = astd_g->getW();		//mirar
			dest.h = astd_g->getH();
			src.x = i * (510 / AST_F);
			src.y = cont2 * (500 / AST_C);
			src.w = 510 / AST_F;
			src.h = 500 / AST_C;
			gold_asteroids->render(src, dest);
		}
		for (auto b : bullet) {

			Transform* transb = mngr_->getComponent<Transform>(b);
			SDL_Rect dest;
			dest.x = transb->getPos().getX();
			dest.y = transb->getPos().getY();
			dest.w = transb->getW();
			dest.h = transb->getH();
			bullet_texture->render(dest, transb->getR());


		}
		for (auto p : powerup1) {
			Transform* trans = mngr_->getComponent<Transform>(p);
			FramedImage* f = mngr_->getComponent<FramedImage>(p);
			
			int cont = f->getCont();
			int cont2 = f->getCont2();
			int i = f->getI();
			cont++;
			if (cont >= 5) {
				i++;
				cont = 0;
			}
			if (i == 7) {
				cont2++;
				cont2 %= 8;
				i = 0;
			}
			i = i % 7;
			f->setCont(cont);
			f->setCont2(cont2);
			f->setI(i);
			SDL_Rect dest, src;
			dest.x = trans->getPos().getX();
			dest.y = trans->getPos().getY();
			dest.w = trans->getW();		//mirar
			dest.h = trans->getH();

			if (f->gettexture() ==&sdlutils().instance()->images().at("powerup1")) {
				src.x = i * (540.75 / 7);
				src.y = cont2 * (618 / 8);
				src.w = 540.75 / 7;
				src.h = 618 / 8;
			}
			else {
				src.x = 0;
				src.y = 0;
				src.w = 300;
				src.h = 180;
			}
			
			f->gettexture()->render(src, dest);

		}


	}
	
	
	SDL_RenderPresent(renderer);
	SDL_Delay(50);
	
	
}
// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. 
void RenderSystem::onRoundStart() {
	
	winner_ = 0;
}
void RenderSystem::onRoundOver() {
	state_ = 0;
	winner_ = 0;

}
void RenderSystem::onGameStart() {
	state_ = 0;
	winner_ = 0;

}
void RenderSystem::onGameOver(bool w) {
	
	if (w) {
		winner_ = 2;
		
	}
	else winner_ = 1;

}