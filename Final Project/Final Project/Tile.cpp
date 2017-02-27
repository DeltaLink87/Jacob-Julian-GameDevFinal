#include "Tile.h"

#include <iostream>
#include <math.h>

Tile::Tile(int x, int y, int width, int height) : Entity(x, y, width, height){
	sprite.setFillColor(sf::Color::Red);
}

Tile::~Tile() { }

void Tile::update(float deltaTime) {

}

void Tile::hit(Entity* hitThis) {
	//std::cout << "tile hit" << std::endl;
	/*sf::RectangleShape smallerHitBox = sf::RectangleShape(sf::Vector2f(hitThis->hitBox.getSize().x / 2 * 1, hitThis->hitBox.getSize().y / 2 * 1));

	smallerHitBox.setPosition(sf::Vector2f(hitThis->hitBox.getPosition().x + hitThis->hitBox.getSize().x / 4, hitThis->hitBox.getPosition().y));
	if (intersects(smallerHitBox)) {
		hitThis->setPostion(sf::Vector2f(hitThis->position.x, hitBox.getPosition().y + hitBox.getSize().y));
		//std::cout << "bottom" << std::endl;
	}

	smallerHitBox.setPosition(sf::Vector2f(hitThis->hitBox.getPosition().x, hitThis->hitBox.getPosition().y + hitThis->hitBox.getSize().y / 4));
	if (intersects(smallerHitBox)) {
		hitThis->setPostion(sf::Vector2f(hitBox.getPosition().x + hitBox.getSize().x, hitThis->hitBox.getPosition().y));
		//std::cout << "right" << std::endl;
	}

	smallerHitBox.setPosition(sf::Vector2f(hitThis->hitBox.getPosition().x + hitThis->hitBox.getSize().x / 4, hitThis->hitBox.getPosition().y + hitThis->hitBox.getSize().y / 2));
	if (intersects(smallerHitBox)) {
		hitThis->setPostion(sf::Vector2f(hitThis->position.x, hitBox.getPosition().y - hitThis->hitBox.getSize().y));
		//std::cout << "top" << std::endl;
	}

	smallerHitBox.setPosition(sf::Vector2f(hitThis->hitBox.getPosition().x + hitThis->hitBox.getSize().x / 2, hitThis->hitBox.getPosition().y + hitThis->hitBox.getSize().y / 4));
	if (intersects(smallerHitBox)) {
		hitThis->setPostion(sf::Vector2f(hitBox.getPosition().x - hitThis->hitBox.getSize().x, hitThis->hitBox.getPosition().y));
		//std::cout << "left" << std::endl;
	}*/

	float difX = (hitBox.getPosition().x + hitBox.getSize().x / 2) - (hitThis->hitBox.getPosition().x + hitThis->hitBox.getSize().x / 2);
	float difY = (hitBox.getPosition().y + hitBox.getSize().y / 2) - (hitThis->hitBox.getPosition().y + hitThis->hitBox.getSize().y / 2);

	if (abs(difX) < abs(difY)) {
		if (difY < 0) {
			hitThis->setPostion(sf::Vector2f(hitThis->position.x, hitBox.getPosition().y + hitBox.getSize().y));
			std::cout << "bottom" << std::endl;
		}
		else {
			hitThis->setPostion(sf::Vector2f(hitThis->position.x, hitBox.getPosition().y - hitThis->hitBox.getSize().y));
			std::cout << "top" << std::endl;
		}
	}
	else if (abs(difX) != abs(difY)) {
		if (difX < 0) {
			hitThis->setPostion(sf::Vector2f(hitBox.getPosition().x + hitBox.getSize().x, hitThis->hitBox.getPosition().y));
			std::cout << "right" << std::endl;
		}
		else {
			hitThis->setPostion(sf::Vector2f(hitBox.getPosition().x - hitThis->hitBox.getSize().x, hitThis->hitBox.getPosition().y));
			std::cout << "left" << std::endl;
		}
	}
}