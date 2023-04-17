#pragma once
#include <stack>
#include <list>
#include <SDL.h>

#include "../game/Game.h"
#include "../ecs/Manager.h"
#include "../utils/Singleton.h"


class GameStateMachine: public Singleton <GameStateMachine>
{
private:
	stack<Manager*> gamestate_stack;
	list<Manager*> gamestate_list;
	bool exit, gameOver, win, next_level;

	Game* g;
public:
	GameStateMachine() ;
	Manager* currentState()const;
	void  pushState(Manager* state);
	void changeState(Manager* state);
	void popState();
	void empty_stack();
	void for_list();
	void run();
	void render();
	void update();
	void handleEvents();
	void Exit_true();
	bool empty_stack_() {
		return gamestate_stack.empty();
	}
	//void setLifes(int n);
	virtual ~GameStateMachine();

	void init();

};

