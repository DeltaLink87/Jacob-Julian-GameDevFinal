#include "TopTile.h"



TopTile::TopTile(int x, int y, int width, int height) : Tile(x, y, width, height) {
	solid = false;
	//sprite.setFillColor(sf::Color::Green);
	textureName = "Tiles/TopLadderTile";
}

TopTile::~TopTile() { }

void TopTile::hit(Entity* hitThis) {
	if (!hitThis->droppedDown && hitThis->getVelocity().y > 0 && hitThis->getPosition().y + hitThis->getHitBox().getSize().x > position.y && hitThis->getPosition().y + hitThis->getHitBox().getSize().x < position.y + hitBox.getSize().y / 10) {
		hitThis->hitWall(sf::Vector2f(hitThis->getPosition().x, position.y - hitThis->getHitBox().getSize().x), 2);
	}
	hitThis->nextToClimbable = true;
}