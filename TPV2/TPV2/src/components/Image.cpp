//#pragma once
//#include "Image.h"
//#include "../ecs/Entity.h"
//Image::Image( Texture* t) {
//	
//	texture = t;
//}
//
//Image::~Image() {
//
//}
//
//void Image::initComponent() {
//	trans = ent_->getComponent<Transform>(int(_TRANSFORM_H_));
//}
//void Image::render() {
//	SDL_Rect dest;
//	dest.x = trans->getPos().getX();
//	dest.y = trans->getPos().getY();
//	dest.w = trans->getW();		//mirar
//	dest.h = trans->getH();
//	texture->render(dest,trans->getR());
//
//}