#include "ChestTile.h"


ChestTile::ChestTile(int x, int y, int width, int height, Item* item) : Tile(x, y, width, height) {
	textureName = "MissingTexture";

	this->treasure = item;

	chest = true;
}

ChestTile::~ChestTile() {


}





bool ChestTile::hitPlayer(Player* hitThis) {

	if (hitThis->up && !this->opened) {
		this->opened = true;

		return true;
	}

}

Item* ChestTile::getTreasure() {
	return treasure;

}