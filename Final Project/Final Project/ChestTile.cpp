#include "ChestTile.h"


ChestTile::ChestTile(int x, int y, int width, int height, Item* item) : Tile(x, y, width, height) {
	textureName = "Tiles/ChestTile";

	this->treasure = item;

	chest = true;
}

ChestTile::~ChestTile() {


}



void ChestTile::hit(Entity* hitThis) { 
	if (hitThis->isPlayer) {
		if (hitPlayer(dynamic_cast<Player*>(hitThis))) {
			dynamic_cast<Player*>(hitThis)->addInventory(treasure);
			treasure = NULL;
		}
	}
}



bool ChestTile::hitPlayer(Player* hitThis) {

	if (hitThis->up && !this->opened) {
		this->opened = true;
		textureName = "Tiles/OpenChestTile";
		spriteInitialized = false;
		return true;
	}
	return false;
}

Item* ChestTile::getTreasure() {
	return treasure;

}