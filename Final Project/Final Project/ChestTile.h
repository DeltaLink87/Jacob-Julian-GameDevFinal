#pragma once

#include "Renderable.h"
#include "Updatable.h"
#include "Equipment.h"
#include "Loot.h"
#include "Tile.h"
#include "Player.h"

class ChestTile : public Tile {
public:
	ChestTile(int, int, int, int, Item*);
	~ChestTile();



	Item* treasure;

	bool opened = false;


	bool hitPlayer(Player*);

	Item* getTreasure();



};