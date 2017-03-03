#include "Actor.h"



Actor::Actor(int x, int y, int width, int height) : Entity(x, y, width, height) { }

Actor::~Actor() { }


std::vector<Attack*>& Actor::getAttacks() { return newAttacks; }
void Actor::gotAttacks() { newAttacks.clear(); }

std::vector<Sound>& Actor::getSounds() { return newSounds; }
void Actor::gotSounds() { newSounds.clear(); }

void Actor::dealDamage(float damage) {
	curHealth -= damage;
}