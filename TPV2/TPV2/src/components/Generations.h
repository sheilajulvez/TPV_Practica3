#pragma once
#include "../ecs/Component.h"
#include "../utils/checkML.h"
struct Generations:public Component
{
public:
	constexpr static cmpId_type id = _GENERATIONS_H;
	Generations(int size);
	virtual~Generations();
	enum state
	{
		Big=3, medium=2, small=1
	};
	int getState() const;
	void setState(int s);
private:
	state current;
};

