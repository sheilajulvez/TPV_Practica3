#pragma once
#include "../game/ecs_defs.h"
class Entity;
class Manager;
struct Component {
	Component() : ent_(), mngr_() { }
	virtual ~Component() { }
	inline void setContext(Entity* ent, Manager* mngr) {
		ent_ = ent;
		mngr_ = mngr;
	}
	virtual void initComponent() { }
	virtual void update() { }
	virtual void render() { }
protected:
	Entity* ent_;
	Manager* mngr_;
};

