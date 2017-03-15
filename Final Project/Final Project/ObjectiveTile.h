#pragma once
#include "Tile.h"
#include "Objective.h"

class ObjectiveTile : public Tile, public Objective
{
public:
	ObjectiveTile(int, int, int, int);
	~ObjectiveTile();

	void reset();
	void hit(Entity*);
};

