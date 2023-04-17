#include "Generations.h"
Generations::Generations(int size) {
	current = state(size);
}
Generations::~Generations() {

}
int Generations::getState() const {
	return current;
}
void Generations::setState(int s) {
	current = state(s);
}
