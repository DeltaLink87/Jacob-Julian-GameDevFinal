#pragma once

#include "Player.h"
#include "Tile.h"
#include "Enemy.h"

class Model {
public:
	Model();
	~Model();

	void update(float);

	Player player;

	Enemy* test;

	int mapWidth, mapHeight, tileSize;
	std::vector<Tile> tileMap;

};

