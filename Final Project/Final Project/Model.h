#pragma once

#include "Player.h"
#include "Tile.h"
#include "Attack.h"
#include "Sound.h"
#include "Enemy.h"
#include "Loot.h"
#include "CraftingMenu.h"
#include "InventoryMenu.h"
#include "MainMenu.h"
#include "LevelManager.h"
#include "Objective.h"

class Model {
public:
	Model();
	~Model();

	void loadLevel(std::string);
	void deallocteLevel();
	void changeLevel(std::string);

	void update(float);
	void updateModel(float);
	void collisionDetection();

	Player* player;

	std::vector<Attack*> attacks;
	std::vector<Sound> sounds;
	std::vector<Enemy*> enemies;
	std::vector<Objective*> levelObjectives;

	LevelManager levelManager;
	bool loadingLevel = false;

	int mapWidth, mapHeight, tileSize;
	Tile*** tileMap;
	std::string curLevelName;
	std::vector<std::string> levelNames;
	int curLevelNum;

	std::vector<Loot*> droppedLoot;
	ItemManager* itemManager = new ItemManager();
	CraftingMenu* craftMenu;
	InventoryMenu* invMenu;
	MainMenu mainMenu;
	int gameMode = 0;

	bool renderDone = false;
};

/*
	loot drops
	player inventory
*/