#include "Projectile.h"



Projectile::Projectile(int x, int y, int width, int height, sf::Vector2f newVel, Actor* newSource, Item* item) : Attack(x, y, width, height, newSource){
	velocity = newVel;

	if (item != NULL)
		damage = item->attack + 1;
	this->type = 0;
	this->melee = false;
	this->piercing = false;

	spriteRotation = (float)atan(velocity.y / velocity.x);
	if (velocity.x < 0)
		spriteRotation += 2 * acos(0);

	hitBox = sf::RectangleShape(sf::Vector2f(abs(cos(spriteRotation) * spriteWidth) + abs(sin(spriteRotation) * spriteHeight), abs(cos(spriteRotation) * spriteHeight) + abs(sin(spriteRotation) * spriteWidth)));

	float angle = atan((float)spriteHeight / (float)spriteWidth);
	float disToFarCorner = sqrt(pow(spriteWidth, 2) + pow(spriteHeight, 2));
	sf::Vector2f corner1(cos(spriteRotation) * spriteWidth, sin(spriteRotation) * spriteWidth);
	sf::Vector2f corner2(cos(spriteRotation + angle) * disToFarCorner, sin(spriteRotation + angle) * disToFarCorner);
	sf::Vector2f corner3(cos(spriteRotation + acos(0)) * spriteHeight, sin(spriteRotation + acos(0)) * spriteHeight);
	spritePositionDifference = sf::Vector2f(std::min(std::min(.0f, corner1.x), std::min(corner2.x, corner3.x)), std::min(std::min(.0f, corner1.y), std::min(corner2.y, corner3.y)));

	spriteRotation = 90 * spriteRotation / acos(0);
}


Projectile::~Projectile() { }


void Projectile::update(float deltaTime) {
	position += velocity * deltaTime;
	hitBox.setPosition(position + spritePositionDifference);
}