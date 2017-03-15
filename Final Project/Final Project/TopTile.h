#pragma once
#include "Tile.h"
class TopTile : public Tile {
public:
	TopTile(int, int, int, int);
	~TopTile();

	void hit(Entity*);
};

