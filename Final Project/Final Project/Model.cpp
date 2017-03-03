#include "Model.h"

#include <iostream>
#include <fstream>

Model::Model(){
	std::ifstream fileHndl;

	//loading the tileamp file
	fileHndl.open("Assets/tilemap2.txt");

	//getting the size of the map
	fileHndl >> mapWidth;
	fileHndl >> mapHeight;
	tileSize = 32;

	//setting the player location
	//playerX = mapCols / 2;
	//playerY = mapRows / 2;

	//loading the type of tile in the map
	//mapData = new int *[mapRows];
	for (int y = 0; y < mapHeight; y++) {
		//mapData[i] = new int[mapCols];
		for (int x = 0; x < mapWidth; x++) {
			int tileType;
			fileHndl >> tileType;
			if (tileType == 1)
				tileMap.push_back(Tile(x * tileSize, y * tileSize, tileSize, tileSize));
			else if (tileType == 2)
				player.setPostion(sf::Vector2f(x * tileSize, y * tileSize));
			else if (tileType == 3)
				test = new Enemy(sf::Vector2f(x*tileSize, y*tileSize));
		}
	}
}

Model::~Model(){ }

void Model::update(float deltaTime) {
	player.update(deltaTime);	//updates player
	//adds new player attacks to the list of attacks currently being made
	if (!player.newAttacks.empty()) {
		for (std::vector<Attack*>::iterator i = player.newAttacks.begin(); i != player.newAttacks.end(); i++) {
			attacks.push_back(*i);
		}
		player.newAttacks.clear();
	}
	//adds new player sounds to the list of sounds currently being made
	if (!player.newSounds.empty()) {
		for (std::vector<Sound>::iterator i = player.newSounds.begin(); i != player.newSounds.end(); i++) {
			sounds.push_back(*i);
		}
		player.newSounds.clear();
	}

	//updating all attacks
	for (std::vector<Attack*>::iterator i = attacks.begin(); i != attacks.end(); ) {
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
	test->updateBehavior(deltaTime, &player, 1);

	//updating tile map
	for (std::vector<Tile>::iterator i = tileMap.begin(); i != tileMap.end(); i++) {
		if (player.intersects(i->hitBox)) {
			player.hit(&(*i));
			i->hit(&player);
		}
		if (test->intersects(i->hitBox)) {
			test->hit(&(*i));
			i->hit(test);
		}
	}
}