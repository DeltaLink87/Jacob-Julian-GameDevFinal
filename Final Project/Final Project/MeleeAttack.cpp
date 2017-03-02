#include "MeleeAttack.h"



MeleeAttack::MeleeAttack(int x, int y, int width, int height, float dir, Actor* newSource) : Attack(x, y, width, height, newSource) {
	direction = dir;
}

MeleeAttack::~MeleeAttack() { }

void MeleeAttack::update(float deltaTime) {
	position.x = source->position.x + source->hitBox.getSize().x / 4 + source->hitBox.getSize().x * cos(direction);
	position.y = source->position.y + source->hitBox.getSize().y / 4 + source->hitBox.getSize().y * sin(direction);

	duration -= deltaTime;
	if (duration < 0)
		remove();
}