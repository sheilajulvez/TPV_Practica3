#pragma once
#include "../game/ecs_defs.h"
#include "Entity.h"
#include "../utils/Vector2D.h"

struct Message {

	msgId_type id;
	// M_COLLISION_BULLET_ASTEROID
	struct {
		Entity* a;
		bool power = false;
	}asteroid_collision_bullet;
	struct {
		Vector2D pos;
		Vector2D vel;
		double width; 
		double height;
		double rotation;
	}bullet_spawn;
	struct {
		bool winner;
	}end;

	struct {
		Entity* f;
		bool pepe;
	}f;
	
	
};