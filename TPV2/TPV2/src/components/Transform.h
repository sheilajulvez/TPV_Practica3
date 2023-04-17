#pragma once
#include "../ecs/Component.h"
#include<iostream>
#include "../utils/Vector2D.h"
#include <math.h>
#include "../utils/checkML.h"
#define PI 3.14159265
struct Transform : public Component {
private:
	Vector2D position;
	Vector2D velocity;
	float width;
	float height;
	float rotation;
	float thrust = 0.4;
	float speedLimit = 3.0;
	Vector2D dir;

public:
	constexpr static cmpId_type id = _TRANSFORM_H_;
	Transform();
	Transform(Vector2D Position, Vector2D Velocity, float Width, float Heigth, float Rotation = 0);
	virtual ~Transform() {}
	void update();
	float getW();
	float getH();
	float getR();
	void RotationVector();
	inline Vector2D getPos() { return position;}
	void setPos(Vector2D p) { position = p;}
	inline Vector2D getVel() { return velocity;}
	inline Vector2D getDir() { return dir; }
	//inline void Acceleration() {

	//	setVel(velocity + Vector2D(0, -1).rotate(rotation) * thrust);
	///*	if (velocity.getX() > speedLimit || velocity.getY()>speedLimit) {
	//		velocity = velocity.normalize() * speedLimit;
	//	}*/
	//	
	//}
	void setR(float valRot);
	void setH(float valHei);
	void setW(float valWid);
	void setVel(Vector2D Velocity);
};