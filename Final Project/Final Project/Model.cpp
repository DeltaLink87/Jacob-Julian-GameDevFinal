#include "Model.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Model::Model(){
	curLevelNum = 0;
	levelNames.push_back("Basic");
	levelNames.push_back("PathFindngTest");
	levelNames.push_back("DropPathTest");
	levelNames.push_back("First Enemy");
	levelNames.push_back("tileMap2");
	levelNames.push_back("VerticalSlice");

	gameMode = 7;

	tileSize = 32;

	craftMenu = new CraftingMenu(itemManager, player);
	invMenu = new InventoryMenu(itemManager, player);

	loadLevel("tileMap2");

	mainMenu.totalStages = levelNames.size();

	//Kept to test weapons at the start.
	player->addInventory(itemManager->getItem("Dagger", 1));
	player->addInventory(itemManager->getItem("Health_Potion", 1));
}

Model::~Model(){ 
	deallocteLevel();

	delete itemManager;
	delete craftMenu;
	delete invMenu;
}


void Model::loadLevel(std::string levelName) {
	levelManager.loadLevelFile(levelName, itemManager);
	levelManager.createLevel(tileMap, mapWidth, mapHeight, tileSize, enemies, levelObjectives, player, itemManager, map);
	//for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
	//	std::cout << (*i)->patrolPath.at(0).x << "," << (*i)->patrolPath.at(0).y << std::endl;
	craftMenu->setPlayer(player);
	invMenu->setPlayer(player);
	loadingLevel = true;
}

void Model::deallocteLevel() {
	delete player;

	for (std::vector<Enemy*>::iterator e = enemies.begin(); e != enemies.end(); ) {
		Enemy* deletedEnemy = *e;
		e = enemies.erase(e);
		delete deletedEnemy;
	}
	enemies.clear();

	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			delete tileMap[y][x];
		}
		delete tileMap[y];
	}
	delete tileMap;

	for (std::vector<Attack*>::iterator a = attacks.begin(); a != attacks.end(); ) {
		Attack* deletedAttack = *a;
		a = attacks.erase(a);
		delete deletedAttack;
	}
	attacks.clear();

	for (std::vector<Loot*>::iterator l = droppedLoot.begin(); l != droppedLoot.end(); ) {
		Loot* deletedLoot = *l;
		delete deletedLoot->getDrop();
		l = droppedLoot.erase(l);
		delete deletedLoot;
	}
	droppedLoot.clear();

	delete map;

	sounds.clear();
	levelObjectives.clear();
}

void Model::changeLevel(std::string levelName) {
	std::cout << "saving player inventory" << std::endl;
	levelManager.savePlayerInventory(player);
	std::cout << "deallocating level" << std::endl;
	deallocteLevel();
	std::cout << "loading level" << std::endl;
	loadLevel(levelName);
	std::cout << "loading player inventory" << std::endl;
	levelManager.loadPlayerInventory(player);
	//for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
	//	std::cout << (*i)->patrolPath.at(0).x << "," << (*i)->patrolPath.at(0).y << std::endl;
	std::cout << "done" << std::endl;
}


void Model::update(float deltaTime) {
	//std::cout << player->getPosition().x << "," << player->getPosition().y << std::endl;

	if (gameMode == 0) {
		renderDone = false;
		//for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
		//	std::cout << (*i)->patrolPath.at(0).x << "," << (*i)->patrolPath.at(0).y << std::endl;
		updateModel(deltaTime);
		collisionDetection();
		//for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
		//	std::cout << (*i)->patrolPath.at(0).x << "," << (*i)->patrolPath.at(0).y << std::endl;

		int stop;
		//std::cin >> stop;

		bool levelComplete = true;
		for (std::vector<Objective*>::iterator o = levelObjectives.begin(); o != levelObjectives.end(); o++) {
			if (!(*o)->isComplete())
				levelComplete = false;
			(*o)->reset();
		}
		if (levelObjectives.size() == 0)
			levelComplete = false;

		if (player->craftingMenu)
			gameMode = 1;
		else if (player->inventoryMenu)
			gameMode = 2;
		else if (levelComplete) {
			gameMode = 3;
			curLevelNum++;
		}
	}
	else if (gameMode == 1) {
		craftMenu->update(deltaTime);
		if (craftMenu->craftingMenu)
			gameMode = 0;
		else if (player->inventoryMenu) {
			craftMenu->craftingMenu = true;
			player->craftingMenu = false;
			gameMode = 2;
		}
	}
	else if (gameMode == 2) {
		invMenu->update(deltaTime);
		if (invMenu->inventoryMenu)
			gameMode = 0;
		else if (player->craftingMenu) {
			invMenu->inventoryMenu = true;
			player->inventoryMenu = false;
			gameMode = 1;

		}
	}
	else if (gameMode == 3) {
		if (player->select)
			gameMode = 4;
	}
	else if (gameMode == 4) {
		if (renderDone)
			gameMode = 5;
	}
	else if (gameMode == 5) {
		renderDone = false;
		changeLevel(levelNames.at(curLevelNum % levelNames.size()));
		//curLevelName = "VerticalSlice";
		gameMode = 6;
	}
	else if (gameMode == 6) {
		if (renderDone)
			gameMode = 0;
	}
	else if (gameMode == 7) {
		mainMenu.update(deltaTime);
		if (mainMenu.start) {
			if (!mainMenu.stageSelect) {
				gameMode = 4;
				curLevelNum = 0;
			}
			else {
				gameMode = 4;
				curLevelNum = mainMenu.getCurSelect();
				mainMenu.stageSelect = false;
			}
		}
	}
}


void Model::updateModel(float deltaTime) {
	player->update(deltaTime);	//updates player

	//adds new player attacks to the list of attacks currently being made
	if (!player->newAttacks.empty()) {
		for (std::vector<Attack*>::iterator i = player->newAttacks.begin(); i != player->newAttacks.end(); i++)
			attacks.push_back(*i);
		player->gotAttacks();
	}
	//adds new player sounds to the list of sounds currently being made
	if (!player->getSounds().empty()) {
		for (std::vector<Sound>::iterator i = player->getSounds().begin(); i != player->getSounds().end(); i++)
			sounds.push_back(*i);
		player->gotSounds();
	}

	//updating enemies
	for (std::vector<Enemy*>::iterator e = enemies.begin(); e != enemies.end(); e++) {
		if (!(*e)->isRemoved()) {
			(*e)->update(deltaTime);

			if (!(*e)->newAttacks.empty()) {
				for (std::vector<Attack*>::iterator i = (*e)->newAttacks.begin(); i != (*e)->newAttacks.end(); i++) {
					attacks.push_back(*i);
				}
				(*e)->newAttacks.clear();
			}

			if ((*e)->isRemoved()) {
				Loot* dropped = (*e)->lootDrop();
				//std::cout << dropped << std::endl;
				if (dropped != NULL)
					droppedLoot.push_back(dropped);
			}
		}
	}

	//updating all attacks
	for (std::vector<Attack*>::iterator i = attacks.begin(); i != attacks.end(); ) {
		if (!(*i)->isRemoved())
			(*i)->update(deltaTime);

		if ((*i)->isRemoved()) {
			Attack* removedAttack = *i;
			i = attacks.erase(i);
			delete removedAttack;
		}
		else i++;
	}

	//updating all sounds
	for (std::vector<Sound>::iterator i = sounds.begin(); i != sounds.end(); ) {
		i->update(deltaTime);

		if (i->done()) {
			i = sounds.erase(i);
		}
		else i++;
	}
}


void Model::collisionDetection() {
	// -----------------------player collision detection--------------------- //
	//player collision against the map
	for (int y = std::max(0, (int)(player->getPosition().y / tileSize)); y < std::min(mapHeight, (int)((player->getPosition().y + player->getHitBox().getSize().y) / tileSize + 1)); y++)
		for (int x = std::max(0, (int)(player->getPosition().x / tileSize)); x < std::min(mapWidth, (int)((player->getPosition().x + player->getHitBox().getSize().x) / tileSize + 1)); x++)
			if (player->intersects(tileMap[y][x]->getHitBox()))
				tileMap[y][x]->hit(player);

	//player collision against other attacks
	for (std::vector<Attack*>::iterator a = attacks.begin(); a != attacks.end(); a++) 
		if ((*a)->intersects(player->getHitBox()))
			(*a)->hitActor(player);

	for (std::vector<Loot*>::iterator l = droppedLoot.begin(); l != droppedLoot.end(); ) {
		if ((*l)->intersects(player->getHitBox())) {
			Loot* removedLoot = *l;
			l = droppedLoot.erase(l);
			player->addInventory(removedLoot->getDrop());
			delete removedLoot;
		}
		else l++;
	}
	// ---------------------player collision detection end-------------------- //

	// -----------------------Enemy collision detection--------------------- //
	for (std::vector<Enemy*>::iterator e = enemies.begin(); e != enemies.end(); e++) {
		//enemy collision against map
		for (int y = std::max(0, (int)((*e)->getPosition().y / tileSize)); y < std::min(mapHeight, (int)(((*e)->getPosition().y + (*e)->getHitBox().getSize().y) / tileSize + 1)); y++)
			for (int x = std::max(0, (int)((*e)->getPosition().x / tileSize)); x < std::min(mapWidth, (int)(((*e)->getPosition().x + (*e)->getHitBox().getSize().x) / tileSize + 1)); x++)
				if ((*e)->intersects(tileMap[y][x]->getHitBox()))
					tileMap[y][x]->hit(*e);

		(*e)->doesSee(player);	//checking if the enemy can see the player

		//checking if the enemy can hear any sounds
		for (std::vector<Sound>::iterator s = sounds.begin(); s != sounds.end(); s++)
			(*e)->doesHear(&(*s));

		//enemy collision against attacks
		for (std::vector<Attack*>::iterator a = attacks.begin(); a != attacks.end(); a++) 
			if ((*a)->intersects((*e)->getHitBox()))
				(*a)->hitActor(*e);
	}
	// ---------------------Enemy collision detection end-------------------- //

	// -----------------------Attack collision detection--------------------- //
	for (std::vector<Attack*>::iterator a = attacks.begin(); a != attacks.end(); a++) {
		//attack collision against map
		for (int y = std::max(0, (int)((*a)->getPosition().y / tileSize)); y < std::min(mapHeight, (int)(((*a)->getPosition().y + (*a)->getHitBox().getSize().y) / tileSize + 1)); y++) {
			for (int x = std::max(0, (int)((*a)->getPosition().x / tileSize)); x < std::min(mapWidth, (int)(((*a)->getPosition().x + (*a)->getHitBox().getSize().x) / tileSize + 1)); x++) {
				if ((*a)->intersects(tileMap[y][x]->getHitBox())) {
					tileMap[y][x]->hit(*a);
					(*a)->hitTile(tileMap[y][x]);
				}
			}
		}
	}
	// ---------------------Attack collision detection end-------------------- //
}