#pragma once

#include "Entity.h"

class Tile : public Entity {
public:
	Tile(int, int, int, int);
	~Tile();

	void update(float);

	void hit(Entity*);
};

