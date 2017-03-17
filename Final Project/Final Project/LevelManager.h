#pragma once
#include <string>

#include "Player.h"
#include "Tile.h"
#include "LadderTile.h"
#include "SolidTile.h"
#include "TopTile.h"
#include "TopLadderTile.h"
#include "Enemy.h"
#include "Objective.h"
#include "ObjectiveEnemy.h"
#include "ObjectiveTile.h"
#include "MovementMap.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void loadLevelFile(std::string, ItemManager*);
	/*create a new level from whatever the last level loaded was
	Tile***& tilemap, int& mapWidth, int& mapHeight, int& mapWidth, int& tileSize, std::vector<Enemy*>& enemies, Player*& player, ItemManager* itemManager&*/
	void createLevel(Tile***&, int&, int&, int&, std::vector<Enemy*>&, std::vector<Objective*>&, Player*&, ItemManager*, MovementMap*&);
	//void saveState(Tile***&, int&, int&, std::vector<Enemy*>&, Player*&);
	//void loadState(Tile***&, int&, int&, std::vector<Enemy*>&, Player*&);
	void savePlayerInventory(Player*&);
	void loadPlayerInventory(Player*&);

private:
	int** tiles;
	int tileMapWidth, tileMapHeight;

	std::map<std::string, Inventory*> inventories;
	std::map<std::string, std::vector<sf::Vector2f>> patrolPaths;
	void loadEnemyInventory(Enemy*, Inventory&);
	void setEnemyPatrolPath(Enemy*, std::vector<sf::Vector2f>);

	Inventory* savedInventory = NULL;
};

