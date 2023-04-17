#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
struct Health :public Component {
public:
	constexpr static cmpId_type id = _HEALTH_H;
	Health();
	virtual ~Health();
	void LessHealth();
	void ResetHealth();
	int GetHealth() const;
	void render();
	void setHealth(int i);

private:
	int lifes=3, maxlife=3;
	Texture* t;
	



 };