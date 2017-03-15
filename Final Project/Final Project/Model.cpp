#include "Model.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Model::Model(){
	/*std::ifstream fileHndl;

	//loading the tileamp file
	//fileHndl.open("Assets/VerticalSlice.txt");
	fileHndl.open("Assets/tilemap2.txt");

	//getting the size of the map
	fileHndl >> mapWidth;
	fileHndl >> mapHeight;
	tileSize = 32;

	//setting the player location
	//playerX = mapCols / 2;
	//playerY = mapRows / 2;

	//loading the type of tile in the map
	tileMap = new Tile **[mapHeight];
	for (int y = 0; y < mapHeight; y++) {
		tileMap[y] = new Tile*[mapWidth];
		for (int x = 0; x < mapWidth; x++) {
			int tileType;
			fileHndl >> tileType;
			if (tileType == 1)
				tileMap[y][x] = new SolidTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tileType == 4)
				tileMap[y][x] = new LadderTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else if (tileType == 6)
				tileMap[y][x] = new TopTile(x * tileSize, y * tileSize, tileSize, tileSize);
			else 
				tileMap[y][x] = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);

			if (tileType == 2)
				player = new Player(x * tileSize, y * tileSize);
			else if (tileType == 3)
				enemies.push_back(new Enemy(sf::Vector2f(x*tileSize, y*tileSize), itemManager));
		}
	}*/

	tileSize = 32;
	levelManager.loadLevelFile("tileMap2"); 
	levelManager.createLevel(tileMap, mapWidth, mapHeight, tileSize, enemies, player, itemManager);
	loadingLevel = true;

	craftMenu = new CraftingMenu(itemManager, &player);
	invMenu = new InventoryMenu(itemManager, &player);

  //Kept to test weapons at the start.
	this->player.addInventory(itemManager->getItem("Dagger"));
  
	craftMenu = new CraftingMenu(itemManager, player);
	invMenu = new InventoryMenu(itemManager, player);
}

Model::~Model(){ 
	delete(itemManager);
}

void Model::update(float deltaTime) {
	//std::cout << player->getPosition().x << "," << player->getPosition().y << std::endl;

	if (gameMode == 0) {
		updateModel(deltaTime);
		collisionDetection();
		if (player->craftingMenu)
			gameMode = 1;
		else if (player->inventoryMenu)
			gameMode = 2;
		else if (player->changeLevel) {
			levelManager.loadLevelFile("VerticalSlice");
			levelManager.createLevel(tileMap, mapWidth, mapHeight, tileSize, enemies, player, itemManager);
			loadingLevel = true;
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
	for (std::vector<Enemy*>::iterator e = enemies.begin(); e != enemies.end(); ) {
		(*e)->update(deltaTime);

		//adding any new attacks non-melee attacks to the attack vector --CHECK--
    //Melee attacks require their source actor's position for updating, keeping them tied to the source actor ensures that they will be deleted when the enemy is deleted.
		if (!(*e)->newAttacks.empty()) {
			for (std::vector<Attack*>::iterator i = (*e)->newAttacks.begin(); i != (*e)->newAttacks.end();) {
				if (!(*i)->melee) {
					attacks.push_back(*i);
					i = (*e)->newAttacks.erase(i);
				}
				else {
					(*i)->update(deltaTime);
					if ((*i)->isRemoved()) {
						Attack* removedAttack = *i;
						i = (*e)->newAttacks.erase(i);
						delete removedAttack;
					}
					else
						i++;
				}
			}
				
		}

		if ((*e)->isRemoved()) {
			Enemy* removedEnemy = *e;
			e = enemies.erase(e);
			Loot* dropped = removedEnemy->lootDrop();
			if (dropped != NULL)
				droppedLoot.push_back(dropped);
			delete removedEnemy;
		}
		else e++;
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

		//checking if enemy moved over an edge
		if ((int)(((*e)->getPosition().y + (*e)->getHitBox().getSize().y) / tileSize) < mapHeight && (int)(((*e)->getPosition().y + (*e)->getHitBox().getSize().y) / tileSize) >= 0 &&
			(int)(((*e)->getPosition().x + (*e)->getHitBox().getSize().x / 2) / tileSize) < mapWidth && (int)(((*e)->getPosition().x + (*e)->getHitBox().getSize().x / 2) / tileSize) >= 0)
			if (!tileMap[(int)(((*e)->getPosition().y + (*e)->getHitBox().getSize().y) / tileSize)][(int)(((*e)->getPosition().x + (*e)->getHitBox().getSize().x / 2) / tileSize)]->isSolid())
				(*e)->overEdge();

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