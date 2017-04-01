#include "SolidTile.h"

#include <iostream>
#include <math.h>

SolidTile::SolidTile(int x, int y, int width, int height) : Tile(x, y, width, height) {
	//sprite.setFillColor(sf::Color::Red);
	textureName = "Tiles/SolidTile";
	solid = true;
}

SolidTile::~SolidTile() { }

void SolidTile::hit(Entity* hitThis) {
	//calculating the difference between the coordinates of this tile and the other entity
	float difX = (hitBox.getPosition().x + hitBox.getSize().x / 2) - (hitThis->getHitBox().getPosition().x + hitThis->getHitBox().getSize().x / 2);
	float difY = (hitBox.getPosition().y + hitBox.getSize().y / 2) - (hitThis->getHitBox().getPosition().y + hitThis->getHitBox().getSize().y / 2);

	//checking if the entities collided vertically or horizontally
	if (abs(difX) < abs(difY) && abs(abs(difX) - abs(difY)) > 2) {
		//checking vertical dircection hit
		if (difY > 0) {	//other entity hit the bottom of this tile
			hitThis->hitWall(sf::Vector2f(hitThis->getPosition().x, hitBox.getPosition().y + hitBox.getSize().y), 0);
			//std::cout << "bottom" << std::endl;
		}
		else {	//other entity hit the top of this tile
			hitThis->hitWall(sf::Vector2f(hitThis->getPosition().x, hitBox.getPosition().y - hitThis->getHitBox().getSize().y), 2);
			//std::cout << "top" << std::endl;
		}
	}

	else if (abs(abs(difX) - abs(difY)) > 2) {
		//checking vertical dircection hit
		if (difX > 0) {	//other entity hit the right of this tile
			hitThis->hitWall(sf::Vector2f(hitBox.getPosition().x + hitBox.getSize().x, hitThis->getHitBox().getPosition().y), 1);
			//std::cout << "right" << std::endl;
		}
		else {	//other entity hit the left of this tile
			hitThis->hitWall(sf::Vector2f(hitBox.getPosition().x - hitThis->getHitBox().getSize().x, hitThis->getHitBox().getPosition().y), 3);
			//std::cout << "left" << std::endl;
		}
	}
}