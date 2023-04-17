#include "Health.h"
#include "../ecs/Entity.h"
Health::Health() {
	t = &SDLUtils::instance()->images().at("health");
}
Health::~Health() {

}

int Health::GetHealth() const{
	return lifes;
}
void Health::LessHealth() {
	lifes -= 1;
}
void Health::ResetHealth() {
	lifes == maxlife;
}
void Health::setHealth(int i) {
	lifes = i;
}
void Health::render() {
	
	SDL_Rect dest;
	
}