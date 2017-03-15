#include "Loot.h"



Loot::Loot(int x, int y, int width, int height, Item* newLoot) : Entity(x, y, width, height) {
	itemDrop = newLoot;
	sprite = newLoot->smallIcon;
	sprite.setScale((float)width / (float)sprite.getTextureRect().width, (float)height / (float)sprite.getTextureRect().height);
	spriteInitialized = true;
}


Loot::~Loot() { }

void Loot::update(float deltaTime) { }

Item* Loot::getDrop() {
	return itemDrop;
}