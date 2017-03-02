#include "Attack.h"



Attack::Attack(int x, int y, int width, int height, Actor* newSource) : Entity(x, y, width, height) {
	source = newSource;
	sprite.setFillColor(sf::Color::Blue);
}

Attack::~Attack() { }

void Attack::hit(Entity* hitThis) {

}