#include "Entity.h"


Entity::Entity(int x, int y, int width, int height){
	position = sf::Vector2f(x, y);
	sprite = sf::RectangleShape(sf::Vector2f(width, height));
}


Entity::~Entity(){ }
