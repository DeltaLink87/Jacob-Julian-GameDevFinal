#pragma once

#include "Player.h"
#include "Tile.h"
#include "Attack.h"
#include "Sound.h"

class Model {
public:
	Model();
	~Model();

	void update(float);

	Player player;

	std::vector<Attack*> attacks;
	std::vector<Sound> sounds;

	int mapWidth, mapHeight, tileSize;
	std::vector<Tile> tileMap;
};

