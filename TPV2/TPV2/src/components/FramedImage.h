#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../game/ecs_defs.h"
#include "../utils/checkML.h"
struct FramedImage :public Component {
private:
	Texture* texture = nullptr;
	Transform* trans = nullptr;
	int fils, cols;
	int i = 0; int cont = 0,cont2=0;

public:
	inline int getfils() { return fils; };
	inline int getI() { return i; };
	inline int getCont() { return cont; };
	inline int getCont2() { return cont2; };
	inline void setI(int i) { this->i = i; }
	inline void setCont(int cont) { this->cont = cont; }
	inline void setCont2(int cont2) { this->cont2 = cont2; };
	constexpr static cmpId_type id = _FRAMEDIMAGE_H;
	FramedImage(int fils,int cols,Texture* t);
	virtual ~FramedImage();
	void update();
	void initComponent();
	void render();
	inline Texture* gettexture() { return texture; }



};