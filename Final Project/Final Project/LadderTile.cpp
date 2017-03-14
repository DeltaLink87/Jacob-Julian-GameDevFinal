#include "LadderTile.h"



LadderTile::LadderTile(int x, int y, int width, int height) : Tile(x, y, width, height){
	//sprite.setFillColor(sf::Color::Magenta);
	textureName = "Tiles/LadderTile";
}

LadderTile::~LadderTile() { }

void LadderTile::hit(Entity* hitThis) {
	hitThis->nextToClimbable = true;
}