#pragma once
#include "../ecs/Component.h"
class PowerComponent:public Component
{
public :
	constexpr static cmpId_type id = _POWERCOMPONENT_H;
	PowerComponent(bool p) {
		power = p;
	}
	virtual ~PowerComponent(){
	}

	inline bool get() { return power; }
	inline bool set(bool p) {power = p;}
private:
	bool power;
};

