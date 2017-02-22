#pragma once

#include "Player.h"
#include "Tile.h"

class Model {
public:
	Model();
	~Model();

	void update(float);

	Player player;

	int mapWidth, mapHeight, tileSize;
	std::vector<Tile> tileMap;
};

