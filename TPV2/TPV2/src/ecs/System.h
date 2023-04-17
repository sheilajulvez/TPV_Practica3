#pragma once
#include "../game/ecs_defs.h"
#include "../game/Constantes.h"
#include "Message.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/FramedImage.h"


class Manager;
class System {
public:
	virtual ~System() { }
	void setContext(Manager* mngr) {
		mngr_ = mngr;
	}
	virtual void initSystem() { }
	virtual void update() { }
	virtual void receive(const Message& m) { }
protected:
	Manager* mngr_;
};