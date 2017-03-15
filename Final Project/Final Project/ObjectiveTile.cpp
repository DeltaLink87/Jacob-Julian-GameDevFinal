#include "ObjectiveTile.h"



ObjectiveTile::ObjectiveTile(int x, int y, int width, int height) : Tile(x, y, width, height){ }


ObjectiveTile::~ObjectiveTile() { }

void ObjectiveTile::hit(Entity* hitThis) {
	if (hitThis->isPlayer)
		complete = true;
	else complete = false;
}

void ObjectiveTile::reset() {
	complete = false;
}