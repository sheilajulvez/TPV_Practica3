#pragma once
#include "Component.h"
#include "../game/ecs_defs.h"
#include <array>
#include <vector>
#include <bitset>
#include <iostream>



using namespace std;


class Entity {
public:
	Entity(grpId_type gId) {
		
	};
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	virtual ~Entity() {}
	void update();
	void render();
	inline void setContext(Manager* m) {
		this->m = m;
	}

private:
	friend Manager;
	vector<Component*> currCmps_;
	array<Component*, maxComponentId> cmps_;
	bool alive_;
	grpId_type gId_;
	Manager* m;
};

