#include "Transform.h"
#include "../ecs/Entity.h"

using namespace std;
Transform::Transform() : Component() {
	position = new Vector2D(0, 0);
	velocity = new Vector2D(0, 0);
	width = 0;
	height = 0;
	rotation = 0;
}

Transform::Transform(Vector2D Position, Vector2D Velocity, float Width, float Heigth, float Rotation) : Component() {
	position = Position;
	velocity = Velocity;
	width = Width;
	height = Heigth;
	rotation = Rotation;
}

void Transform::update() {
	position = position + velocity;
}

float Transform::getW() {
	return width;
}

float Transform::getH() {
	return height;
}

float Transform::getR() {
	return rotation;
}
//void Transform::RotationVector() {
//	cout << rotation;
//	float x = cos((rotation *PI)/180);
//	float y = sin((rotation * PI)/180);
//	dir = { y,-x };
//}


void Transform::setR(float Rotation) {
	rotation = Rotation;
}

void Transform::setH(float Height) {
	height = Height;
}

void Transform::setW(float Width) {
	width = Width;
}

void Transform::setVel(Vector2D Velocity) {
	
	velocity = Velocity;
}
