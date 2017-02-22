#include "Entity.h"


Entity::Entity(int x, int y, int width, int height){
	position = sf::Vector2f(x, y);
	sprite = sf::RectangleShape(sf::Vector2f(width, height));
	sprite.setPosition(position);
	hitBox = sf::RectangleShape(sf::Vector2f(width, height));
	hitBox.setPosition(position);
}

Entity::~Entity(){ }

bool Entity::intersects(sf::RectangleShape otherHitBox) {
	if (hitBox.getPosition().x < otherHitBox.getPosition().x + otherHitBox.getSize().x &&
		hitBox.getPosition().x + hitBox.getSize().x > otherHitBox.getPosition().x &&
		hitBox.getPosition().y < otherHitBox.getPosition().y + otherHitBox.getSize().y &&
		hitBox.getPosition().y + hitBox.getSize().y > otherHitBox.getPosition().y)
		return true;
	return false;
}

void Entity::setPostion(sf::Vector2f newPosition) {
	position = newPosition;
	hitBox.setPosition(position);
}