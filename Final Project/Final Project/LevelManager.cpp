#include "LevelManager.h"

#include <iostream>
#include <fstream>

LevelManager::LevelManager() { }

LevelManager::~LevelManager() { }


void LevelManager::loadLevelFile(std::string fileName) {
	std::ifstream fileHndl;
	fileHndl.open("Assets/Levels/" + fileName + ".txt");

	fileHndl >> tileMapWidth;
	fileHndl >> tileMapHeight;

	std::cout << tileMapWidth << "," << tileMapHeight << std::endl;

	tiles = new int *[tileMapHeight];
	for (int y = 0; y < tileMapHeight; y++) {
		tiles[y] = new int[tileMapWidth];
		for (int x = 0; x < tileMapWidth; x++) {
			fileHndl >> tiles[y][x];
		}
	}
}

void LevelManager::createLevel(Tile***& tileMap, int& mapWidth, int& mapHeight, int& tileSize, std::vector<Enemy*>& enemies, Player*& player, ItemManager*& itemManager) {
	enemies.clear();

	mapWidth = tileMapWidth;
	mapHeight = tileMapHeight;

	tileMap = new Tile **[mapHeight];
	for (int y = 0; y < mapHeight; y++) {
		tileMap[y] = new Tile*[mapWidth];
		for (int x = 0; x < mapWidth; x++) {
			if (tiles[y][x] == 1)
				tileMap[y][x] = new SolidTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tiles[y][x] == 4)
				tileMap[y][x] = new LadderTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tiles[y][x] == 6)
				tileMap[y][x] = new TopTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else
				tileMap[y][x] = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);

			if (tiles[y][x] == 2) 
				player = new Player(x * tileSize, y * tileSize);
			else if (tiles[y][x] == 3)
				enemies.push_back(new Enemy(sf::Vector2f(x*tileSize, y*tileSize), itemManager));
		}
	}
}

/*void LevelManager::saveState(Tile***& tileMap, int& mapWidth, int& mapHeight, std::vector<Enemy*>& enemies, Player*& player) {

}

void LevelManager::loadState(Tile***& tileMap, int& mapWidth, int& mapHeight, std::vector<Enemy*>& enemies, Player*& player) {

}*/

void LevelManager::savePlayerInventory(Player*& player) {
	savedInventory = new Inventory();
	
	for (int y = 0; y < player->getInventory()->getHeight(); y++) {
		for (int x = 0; x < player->getInventory()->getWidth(); x++) {
			Item* item = player->getInventory()->getCurSeletected(x, y);
			if (item != NULL) 
				savedInventory->addToInventory(new Item(*item), x, y);
		}
	}

	for (int y = 0; y < player->getInventory()->getArmourSlots(); y++) {
		Item* item = player->getInventory()->getCurSeletected(-1, y);
		if (item != NULL)
			savedInventory->addToInventory(new Item(*item), -1, y);
	}
}

void LevelManager::loadPlayerInventory(Player*& player) {
	Inventory* playerInventory = player->getInventory();

	for (int y = 0; y < savedInventory->getHeight(); y++) {
		for (int x = 0; x < savedInventory->getWidth(); x++) {
			Item* item = savedInventory->getCurSeletected(x, y);
			playerInventory->addToInventory(new Item(*item), x, y);
		}
	}

	for (int y = 0; y < savedInventory->getArmourSlots(); y++) {
		Item* item = savedInventory->getCurSeletected(-1, y);
		playerInventory->addToInventory(new Item(*item), -1, y);
	}
}