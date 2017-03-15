#pragma once

#include "Player.h"
#include "Tile.h"
#include "LadderTile.h"
#include "SolidTile.h"
#include "TopTile.h"
#include "Attack.h"
#include "Sound.h"
#include "Enemy.h"
#include "Loot.h"
#include "CraftingMenu.h"
#include "InventoryMenu.h"
#include "LevelManager.h"

class Model {
public:
	Model();
	~Model();

	void update(float);
	void updateModel(float);
	void collisionDetection();

	Player* player;

	std::vector<Attack*> attacks;
	std::vector<Sound> sounds;
	std::vector<Enemy*> enemies;

	LevelManager levelManager;
	bool loadingLevel = false;

	int mapWidth, mapHeight, tileSize;
	Tile*** tileMap;

	std::vector<Loot*> droppedLoot;
	ItemManager* itemManager = new ItemManager();
	CraftingMenu* craftMenu;
	InventoryMenu* invMenu;
	int gameMode = 0;
};

/*
	loot drops
	player inventory
*/