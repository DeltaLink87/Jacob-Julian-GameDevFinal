#include "LevelManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

LevelManager::LevelManager() { }

LevelManager::~LevelManager() { }


void LevelManager::loadLevelFile(std::string fileName, ItemManager* itemManager) {
	std::ifstream fileHndl;
	fileHndl.open("Assets/Levels/" + fileName + ".txt");

	fileHndl >> tileMapWidth;
	fileHndl >> tileMapHeight;

	//std::cout << tileMapWidth << "," << tileMapHeight << std::endl;

	tiles = new int *[tileMapHeight];
	for (int y = 0; y < tileMapHeight; y++) {
		tiles[y] = new int[tileMapWidth];
		for (int x = 0; x < tileMapWidth; x++) {
			fileHndl >> tiles[y][x];
		}
	}

	/*std::string input;
	fileHndl >> input;
	while (input.compare("") == 0)
		fileHndl >> input;*/

	for (std::map<std::string, Inventory*>::iterator i = inventories.begin(); i != inventories.end(); i++)
		delete i->second;
	inventories.clear();

	std::string targetLocation;
	fileHndl >> targetLocation;
	std::string itemName;
	int quantity;
	while (targetLocation.compare("") != 0 && targetLocation.compare("-") != 0) {
		inventories.insert(std::pair<std::string, Inventory*>(targetLocation, new Inventory()));

		fileHndl >> itemName;
		while (itemName.compare("") != 0 && itemName.compare("-") != 0) {
			fileHndl >> quantity;

			//std::cout << targetLocation << " : " << itemName << " : " << quantity << std::endl;
			Item* item = itemManager->getItem(itemName, quantity);
			if (item->armourType > 0)
				inventories.at(targetLocation)->addToInventory(item, -1, item->armourType - 1);
			else inventories.at(targetLocation)->addToInventory(item);

			fileHndl >> itemName;
		}
		fileHndl >> targetLocation;
	}

	patrolPaths.clear();

	fileHndl >> targetLocation;
	int newX = 0, newY = 0;
	while (targetLocation.compare("") != 0 && targetLocation.compare("-") != 0) {
		patrolPaths.insert(std::pair<std::string, std::vector<sf::Vector2f>>(targetLocation, std::vector<sf::Vector2f>()));

		fileHndl >> newX;
		fileHndl >> newY;
		while (newX != -1 && newY != -1) {
			//std::cout << targetLocation << " :!! " << newX << " , " << newY << std::endl;
			patrolPaths.at(targetLocation).push_back(sf::Vector2f(newX * 32 + 16, newY * 32 + 16));

			fileHndl >> newX;
			fileHndl >> newY;
		}
		fileHndl >> targetLocation;
	}
}

void LevelManager::createLevel(Tile***& tileMap, int& mapWidth, int& mapHeight, int& tileSize, std::vector<Enemy*>& enemies, std::vector<Objective*>& objectives, Player*& player, ItemManager* itemManager, MovementMap*& map) {
	mapWidth = tileMapWidth;
	mapHeight = tileMapHeight;

	map = new MovementMap(tiles, tileMapWidth, tileMapHeight);

	tileMap = new Tile **[mapHeight];
	for (int y = 0; y < mapHeight; y++) {
		tileMap[y] = new Tile*[mapWidth];
		for (int x = 0; x < mapWidth; x++) {
			if (tiles[y][x] == 1)
				tileMap[y][x] = new SolidTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tiles[y][x] == 4)
				tileMap[y][x] = new LadderTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tiles[y][x] == 5) {
				ChestTile* chest = new ChestTile(x * tileSize, y * tileSize, tileSize, tileSize);


				std::stringstream ss;
				ss << x << "," << y;
				//std::cout << ss.str() << std::endl;
				if (inventories.count(ss.str()) > 0)
					loadChestItem(chest, *inventories.at(ss.str()));

				tileMap[y][x] = chest;
			}
			else if (tiles[y][x] == 6)
				tileMap[y][x] = new TopLadderTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tiles[y][x] == 8) {
				ObjectiveTile* objective = new ObjectiveTile(x * tileSize, y * tileSize, tileSize, tileSize);
				tileMap[y][x] = objective;
				objectives.push_back(objective);
			}
			else if (tiles[y][x] == 9)
				tileMap[y][x] = new TopTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tiles[y][x] == 10)
				tileMap[y][x] = new ChestTile(x * tileSize, y * tileSize, tileSize);
			else
				tileMap[y][x] = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);

			if (tiles[y][x] == 2) 
				player = new Player(x * tileSize + 12, y * tileSize + 12);
			else if (tiles[y][x] == 3) {
				Enemy* newEnemy = new Enemy(sf::Vector2f(x*tileSize + 12, y*tileSize + 12), itemManager, map);
				
				std::stringstream ss;
				ss << x << "," << y;
				//std::cout << ss.str() << std::endl;
				if (inventories.count(ss.str()) > 0)
					loadEnemyInventory(newEnemy, *inventories.at(ss.str()));

				if (patrolPaths.count(ss.str()) > 0)
					setEnemyPatrolPath(newEnemy, patrolPaths.at(ss.str()));

				enemies.push_back(newEnemy);
			}
			else if (tiles[y][x] == 7) {
				ObjectiveEnemy* objective = new ObjectiveEnemy(sf::Vector2f(x * tileSize + 12, y * tileSize + 12), itemManager, map);

				std::stringstream ss;
				ss << x << "," << y;
				//std::cout << ss.str() << std::endl;
				if (inventories.count(ss.str()) > 0)
					loadEnemyInventory(objective, *inventories.at(ss.str()));

				if (patrolPaths.count(ss.str()) > 0)
					setEnemyPatrolPath(objective, patrolPaths.at(ss.str()));

				enemies.push_back(objective);
				objectives.push_back(objective);
			}
		}
	}
}

/*void LevelManager::saveState(Tile***& tileMap, int& mapWidth, int& mapHeight, std::vector<Enemy*>& enemies, Player*& player) {

}

void LevelManager::loadState(Tile***& tileMap, int& mapWidth, int& mapHeight, std::vector<Enemy*>& enemies, Player*& player) {

}*/

void LevelManager::savePlayerInventory(Player*& player) {
	if (savedInventory != NULL)
		delete savedInventory;
	savedInventory = new Inventory();
	
	for (int y = 0; y < player->getInventory()->getHeight(); y++) {
		for (int x = 0; x < player->getInventory()->getWidth(); x++) {
			Item* item = player->getInventory()->getCurSeletected(x, y);
			if (item != NULL) 
				savedInventory->addToInventory(item->getCopy(), x, y);
		}
	}

	for (int y = 0; y < player->getInventory()->getArmourSlots(); y++) {
		Item* item = player->getInventory()->getCurSeletected(-1, y);
		if (item != NULL)
			savedInventory->addToInventory(item->getCopy(), -1, y);
	}
}

void LevelManager::loadPlayerInventory(Player*& player) {
	Inventory* playerInventory = player->getInventory();

	for (int y = 0; y < savedInventory->getHeight(); y++) {
		for (int x = 0; x < savedInventory->getWidth(); x++) {
			Item* item = savedInventory->getCurSeletected(x, y);
			if (item != NULL)
				playerInventory->addToInventory(item->getCopy(), x, y);
		}
	}

	for (int y = 0; y < savedInventory->getArmourSlots(); y++) {
		Item* item = savedInventory->getCurSeletected(-1, y);
		if (item != NULL)
			playerInventory->addToInventory(item->getCopy(), -1, y);
	}
}

void LevelManager::loadEnemyInventory(Enemy* enemy, Inventory& inventory) {
	Inventory* enemyInventory = enemy->getInventory();

	for (int y = 0; y < inventory.getHeight(); y++) {
		for (int x = 0; x < inventory.getWidth(); x++) {
			Item* item = inventory.getCurSeletected(x, y);
			if (item != NULL)
				enemyInventory->addToInventory(item->getCopy(), x, y);
		}
	}

	for (int y = 0; y < inventory.getArmourSlots(); y++) {
		Item* item = inventory.getCurSeletected(-1, y);
		if (item != NULL)
			enemyInventory->addToInventory(item->getCopy(), -1, y);
	}
}

void LevelManager::setEnemyPatrolPath(Enemy* enemy, std::vector<sf::Vector2f> path) {
	std::vector<sf::Vector2f>* patrolPath = new std::vector<sf::Vector2f>();
	for (std::vector<sf::Vector2f>::iterator i = path.begin(); i != path.end(); i++) 
		patrolPath->push_back((*i));
	
	enemy->setPatrolPath(patrolPath);
}

void LevelManager::loadChestItem(ChestTile* chest, Inventory& inventory) {
	Item* item = inventory.dropRandom();
	if (item != NULL) {
		inventory.addToInventory(new Item(*item));
		chest->treasure = item;
	}
}