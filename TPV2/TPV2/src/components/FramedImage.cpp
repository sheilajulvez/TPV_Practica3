#pragma once
#include "FramedImage.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
FramedImage::FramedImage(int fils, int cols, Texture* t){
	this->fils = fils;
	this->cols = cols;
	texture = t;
}

FramedImage::~FramedImage() {

}
void FramedImage::update() {
	cont++;
	if (cont >= 5) {
		i++;
		cont = 0;
	}
	if (i == fils) {
		cont2++;
		cont2 %= cols;
		i = 0;
	}
	i = i % fils;
}
void FramedImage::initComponent() {
	trans = mngr_->getComponent<Transform>(ent_);
}
void FramedImage::render() {
	SDL_Rect dest, src;
	dest.x = trans->getPos().getX();
	dest.y= trans->getPos().getY();
	dest.w = trans->getW();		//mirar
	dest.h = trans->getH();
	src.x = i*(510 / fils);
	src.y = cont2*(500 / cols);
	src.w = 510/fils ;
	src.h = 500/cols;
	texture->render(src,dest);
}