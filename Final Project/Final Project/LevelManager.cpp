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
	//laoding the tile map
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
	//clearing starting inventories for the previous level loaded
	for (std::map<std::string, Inventory*>::iterator i = inventories.begin(); i != inventories.end(); i++)
		delete i->second;
	inventories.clear();

	//loading starting inventories for enemies and chests
	std::string targetLocation;
	fileHndl >> targetLocation;
	std::string itemName;
	int quantity;
	//looping until getting a - to signify the end of the inventories
	while (targetLocation.compare("") != 0 && targetLocation.compare("-") != 0) {
		inventories.insert(std::pair<std::string, Inventory*>(targetLocation, new Inventory()));

		fileHndl >> itemName;
		//looping until getting a - to signify the end of this inventory
		while (itemName.compare("") != 0 && itemName.compare("-") != 0) {
			fileHndl >> quantity;

			//adding the new item loaded the inventory
			Item* item = itemManager->getItem(itemName, quantity);
			if (item->getArmourType() > 0)
				inventories.at(targetLocation)->addToInventory(item, -1, item->getArmourType() - 1);
			else inventories.at(targetLocation)->addToInventory(item);
			//getting next item
			fileHndl >> itemName;
		}
		//getting next loaction of enemy/chest
		fileHndl >> targetLocation;
	}

	//clearing patrol paths for the last level
	patrolPaths.clear();

	//loading the patrol paths of enemies in this level
	fileHndl >> targetLocation;
	int newX = 0, newY = 0;
	//looping until getting a - to signify the end of the inventories
	while (targetLocation.compare("") != 0 && targetLocation.compare("-") != 0) {
		patrolPaths.insert(std::pair<std::string, std::vector<sf::Vector2f>>(targetLocation, std::vector<sf::Vector2f>()));

		fileHndl >> newX;
		fileHndl >> newY;
		//looping until getting a -1 for x and y to signify the end of this enemies patrol path
		while (newX != -1 && newY != -1) {
			//std::cout << targetLocation << " :!! " << newX << " , " << newY << std::endl;
			patrolPaths.at(targetLocation).push_back(sf::Vector2f(newX * 32 + 16, newY * 32 + 16));

			fileHndl >> newX;
			fileHndl >> newY;
		}
		//getting the location of the next enemy
		fileHndl >> targetLocation;
	}
}

void LevelManager::createLevel(Tile***& tileMap, int& mapWidth, int& mapHeight, int& tileSize, std::vector<Enemy*>& enemies, std::vector<Objective*>& objectives, Player*& player, ItemManager* itemManager, MovementMap*& map) {
	//setting the mapWidth and mapHeight for the game
	mapWidth = tileMapWidth;
	mapHeight = tileMapHeight;
	//setting the map for the game
	map = new MovementMap(tiles, tileMapWidth, tileMapHeight);

	//creating the tilemap for the game
	tileMap = new Tile **[mapHeight];
	for (int y = 0; y < mapHeight; y++) {
		tileMap[y] = new Tile*[mapWidth];
		for (int x = 0; x < mapWidth; x++) {
			//selecting the appropriate tile for the tile number in the file
			if (tiles[y][x] == 1)	//solid
				tileMap[y][x] = new SolidTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tiles[y][x] == 4)	//ladder
				tileMap[y][x] = new LadderTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tiles[y][x] == 5) {	//chest
				ChestTile* chest = new ChestTile(x * tileSize, y * tileSize, tileSize, tileSize);

				//setting the inventory of the chest
				std::stringstream ss;
				ss << x << "," << y;
				//std::cout << ss.str() << std::endl;
				if (inventories.count(ss.str()) > 0)
					loadChestItem(chest, *inventories.at(ss.str()));

				tileMap[y][x] = chest;
			}
			else if (tiles[y][x] == 6)	//top of ladder
				tileMap[y][x] = new TopLadderTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tiles[y][x] == 8) {	//objective location
				ObjectiveTile* objective = new ObjectiveTile(x * tileSize, y * tileSize, tileSize, tileSize);
				tileMap[y][x] = objective;
				objectives.push_back(objective);
			}
			else if (tiles[y][x] == 9)	//tile that can be jumped/dropped through
				tileMap[y][x] = new TopTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tiles[y][x] == 10)	//chest tile
				tileMap[y][x] = new ChestTile(x * tileSize, y * tileSize, tileSize);
			else //empty tile
				tileMap[y][x] = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);

			if (tiles[y][x] == 2)	//setting player at this location 
				player = new Player(x * tileSize + 12, y * tileSize + 12);
			else if (tiles[y][x] == 3) {	//setting enemy at this location
				Enemy* newEnemy = new Enemy(sf::Vector2f(x*tileSize + 12, y*tileSize + 12), itemManager, map);
				
				//setting enemy inventory
				std::stringstream ss;
				ss << x << "," << y;
				//std::cout << ss.str() << std::endl;
				if (inventories.count(ss.str()) > 0)
					loadEnemyInventory(newEnemy, *inventories.at(ss.str()));

				//setting enemy patrol path
				if (patrolPaths.count(ss.str()) > 0)
					setEnemyPatrolPath(newEnemy, patrolPaths.at(ss.str()));

				enemies.push_back(newEnemy);
			}
			else if (tiles[y][x] == 7) {	//setting objective enemy at this location
				ObjectiveEnemy* objective = new ObjectiveEnemy(sf::Vector2f(x * tileSize + 12, y * tileSize + 12), itemManager, map);

				//setting enemy inventory
				std::stringstream ss;
				ss << x << "," << y;
				//std::cout << ss.str() << std::endl;
				if (inventories.count(ss.str()) > 0)
					loadEnemyInventory(objective, *inventories.at(ss.str()));

				//setting enemy patrol path
				if (patrolPaths.count(ss.str()) > 0)
					setEnemyPatrolPath(objective, patrolPaths.at(ss.str()));

				enemies.push_back(objective);
				objectives.push_back(objective);
			}
		}
	}
}

//saving player inventory across levels
void LevelManager::savePlayerInventory(Player*& player) {
	//reseting saved player inventory
	if (savedInventory != NULL)
		delete savedInventory;
	savedInventory = new Inventory();
	
	//copying player items
	for (int y = 0; y < player->getInventory()->getHeight(); y++) {
		for (int x = 0; x < player->getInventory()->getWidth(); x++) {
			Item* item = player->getInventory()->getCurSeletected(x, y);
			if (item != NULL) 
				savedInventory->addToInventory(item->getCopy(), x, y);
		}
	}

	//copying player armour
	for (int y = 0; y < player->getInventory()->getArmourSlots(); y++) {
		Item* item = player->getInventory()->getCurSeletected(-1, y);
		if (item != NULL)
			savedInventory->addToInventory(item->getCopy(), -1, y);
	}
}

//loading the players inventory
void LevelManager::loadPlayerInventory(Player*& player) {
	Inventory* playerInventory = player->getInventory();

	//setting player items
	for (int y = 0; y < savedInventory->getHeight(); y++) {
		for (int x = 0; x < savedInventory->getWidth(); x++) {
			Item* item = savedInventory->getCurSeletected(x, y);
			if (item != NULL)
				playerInventory->addToInventory(item->getCopy(), x, y);
		}
	}

	//setting player armour
	for (int y = 0; y < savedInventory->getArmourSlots(); y++) {
		Item* item = savedInventory->getCurSeletected(-1, y);
		if (item != NULL)
			playerInventory->addToInventory(item->getCopy(), -1, y);
	}
}

//setting enemies inventories
void LevelManager::loadEnemyInventory(Enemy* enemy, Inventory& inventory) {
	Inventory* enemyInventory = enemy->getInventory();

	//setting enemy items
	for (int y = 0; y < inventory.getHeight(); y++) {
		for (int x = 0; x < inventory.getWidth(); x++) {
			Item* item = inventory.getCurSeletected(x, y);
			if (item != NULL)
				enemyInventory->addToInventory(item->getCopy(), x, y);
		}
	}

	//setting enemy armour
	for (int y = 0; y < inventory.getArmourSlots(); y++) {
		Item* item = inventory.getCurSeletected(-1, y);
		if (item != NULL)
			enemyInventory->addToInventory(item->getCopy(), -1, y);
	}
}

//setting enemy patrol path
void LevelManager::setEnemyPatrolPath(Enemy* enemy, std::vector<sf::Vector2f> path) {
	//copying patrol path
	std::vector<sf::Vector2f>* patrolPath = new std::vector<sf::Vector2f>();
	for (std::vector<sf::Vector2f>::iterator i = path.begin(); i != path.end(); i++) 
		patrolPath->push_back((*i));
	
	enemy->setPatrolPath(patrolPath);
}

//setting chest inventory
void LevelManager::loadChestItem(ChestTile* chest, Inventory& inventory) {
	//setting chest contents to random piece of loot from the possible loot it could have
	Item* item = inventory.dropRandom();
	if (item != NULL) {
		inventory.addToInventory(item->getCopy());
		chest->treasure = item;
	}
}