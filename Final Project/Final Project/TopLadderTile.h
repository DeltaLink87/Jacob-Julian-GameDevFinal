#pragma once
#include "Tile.h"
class TopLadderTile :
	public Tile
{
public:
	TopLadderTile(int, int, int, int);
	~TopLadderTile();

	void hit(Entity*);
};

