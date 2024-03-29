#pragma once

#include "Renderable.h"
#include "Updatable.h"
#include "Equipment.h"
#include "Loot.h"
#include "Tile.h"
#include "Player.h"

class ChestTile : public Tile {
public:
	ChestTile(int, int, int, int, Item* = NULL);

	//For creating opened chests
	ChestTile(int, int, int);
	~ChestTile();



	Item* treasure = NULL;

	bool opened = false;

	void hit(Entity*);

	bool hitPlayer(Player*);

	Item* getTreasure();



};