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
		}
	}
}

Model::~Model(){ }

void Model::update(float deltaTime) {
	player.update(deltaTime);

	for (std::vector<Tile>::iterator i = tileMap.begin(); i != tileMap.end(); i++) {
		if (player.intersects(i->hitBox)) {
			player.hit(&(*i));
			i->hit(&player);
		}
	}
}