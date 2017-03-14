#include "Attack.h"

Attack::Attack(int x, int y, int width, int height, Actor* newSource) : Entity(x, y, width, height) {
	source = newSource;
	//sprite.setFillColor(sf::Color::Blue);
	textureName = "Attacks/Attack";
}

Attack::~Attack() { }

void Attack::hitTile(Tile* hitThis) {
	if (hitThis->isSolid())
		remove();
}

void Attack::hitActor(Actor* hitThis) {
	//std::cout << "hit" << std::endl;
	if (hitThis != source) {
		hitThis->dealDamage(damage);
		//std::cout << hitThis->curHealth << std::endl;
		remove();
	}
}