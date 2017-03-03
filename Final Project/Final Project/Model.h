#pragma once

#include "Player.h"
#include "Tile.h"
#include "LadderTile.h"
#include "SolidTile.h"
#include "Attack.h"
#include "Sound.h"
#include "Enemy.h"

class Model {
public:
	Model();
	~Model();

	void update(float);
	void updateModel(float);
	void collisionDetection();

	Player player;

	std::vector<Attack*> attacks;
	std::vector<Sound> sounds;
	std::vector<Enemy*> enemies;

	int mapWidth, mapHeight, tileSize;
	Tile*** tileMap;

};

/*
	loot drops
	player inventory
*/