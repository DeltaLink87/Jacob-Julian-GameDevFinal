#include "Projectile.h"



Projectile::Projectile(int x, int y, int width, int height, sf::Vector2f newVel, Actor* newSource, Item* item) : Attack(x, y, width, height, newSource){
	velocity = newVel;

	this->type = 0;
	this->melee = false;
	this->piercing = false;
}


Projectile::~Projectile() { }


void Projectile::update(float deltaTime) {
	position += velocity * deltaTime;
	hitBox.setPosition(position);
}