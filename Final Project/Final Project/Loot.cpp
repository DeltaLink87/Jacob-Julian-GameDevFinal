#include "Loot.h"



Loot::Loot(int x, int y, int width, int height, Item* newLoot) : Entity(x, y, width, height) {
	itemDrop = newLoot;
}


Loot::~Loot() { }

void Loot::update(float deltaTime) { }

Item* Loot::getDrop() {
	return itemDrop;
}