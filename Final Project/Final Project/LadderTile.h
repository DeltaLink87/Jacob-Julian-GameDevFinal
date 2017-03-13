#pragma once
#include "Tile.h"
class LadderTile :
	public Tile
{
public:
	LadderTile(int, int, int, int);
	~LadderTile();

	void hit(Entity*);
};

