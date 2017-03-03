#include "Actor.h"



Actor::Actor(int x, int y, int width, int height) : Entity(x, y, width, height) { }

Actor::~Actor() { }


void Actor::addInventory(Item* item) {


}

std::vector<Attack*>& Actor::getAttacks() {
	return newAttacks;
}

std::vector<Sound>& Actor::getSounds() {
	return newSounds;
}

