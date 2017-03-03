#include "Projectile.h"



Projectile::Projectile(int x, int y, int width, int height, sf::Vector2f newVel, Actor* newSource) : Attack(x, y, width, height, newSource){
	velocity = newVel;
}


Projectile::~Projectile() { }


void Projectile::update(float deltaTime) {
	position += velocity * deltaTime;
	hitBox.setPosition(position);
}