#pragma once
#include <string>

#include "Player.h"
#include "Tile.h"
#include "LadderTile.h"
#include "SolidTile.h"
#include "TopTile.h"
#include "Enemy.h"
#include "Objective.h"
#include "ObjectiveEnemy.h"
#include "ObjectiveTile.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void loadLevelFile(std::string, ItemManager*);
	/*create a new level from whatever the last level loaded was
	Tile***& tilemap, int& mapWidth, int& mapHeight, int& mapWidth, int& tileSize, std::vector<Enemy*>& enemies, Player*& player, ItemManager* itemManager&*/
	void createLevel(Tile***&, int&, int&, int&, std::vector<Enemy*>&, std::vector<Objective*>&, Player*&, ItemManager*);
	//void saveState(Tile***&, int&, int&, std::vector<Enemy*>&, Player*&);
	//void loadState(Tile***&, int&, int&, std::vector<Enemy*>&, Player*&);
	void savePlayerInventory(Player*&);
	void loadPlayerInventory(Player*&);

private:
	int** tiles;
	int tileMapWidth, tileMapHeight;

	std::map<std::string, Inventory*> inventories;
	void loadEnemyInventory(Enemy*, Inventory&);

	Inventory* savedInventory = NULL;
};

