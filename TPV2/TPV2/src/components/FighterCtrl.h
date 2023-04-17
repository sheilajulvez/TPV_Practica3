#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"

struct FighterCtrl :public Component {
private:
	Transform* trans;
	float acceleration = 2;


public:
	FighterCtrl();
	virtual~FighterCtrl();
	void initComponent();
	void HandleEvent(SDL_Event event);


};