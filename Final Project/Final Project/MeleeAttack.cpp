#include "MeleeAttack.h"



MeleeAttack::MeleeAttack(int x, int y, int width, int height, float dir, Actor* newSource) : Attack(x, y, width, height, newSource) {
	direction = dir;
}

MeleeAttack::~MeleeAttack() { }

void MeleeAttack::update(float deltaTime) {
	position.x = source->getPosition().x + source->getHitBox().getSize().x / 4 + source->getHitBox().getSize().x * cos(direction);
	position.y = source->getPosition().y + source->getHitBox().getSize().y / 4 + source->getHitBox().getSize().y * sin(direction);

	duration -= deltaTime;
	if (duration < 0)
		remove();

	hitBox.setPosition(position);
}

void MeleeAttack::hitTile(Tile*) { }