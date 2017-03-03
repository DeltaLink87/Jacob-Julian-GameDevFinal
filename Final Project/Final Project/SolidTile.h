#pragma once
#include "Tile.h"
class SolidTile :
	public Tile
{
public:
	SolidTile(int, int, int, int);
	~SolidTile();

	void hit(Entity*);

};

