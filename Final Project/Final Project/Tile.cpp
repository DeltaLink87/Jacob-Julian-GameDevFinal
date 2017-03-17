#include "Tile.h"

#include <iostream>
#include <math.h>

Tile::Tile(int x, int y, int width, int height) : Entity(x, y, width, height){
	//sprite.setFillColor(sf::Color::Transparent);
	textureName = "Tiles/EmptyTile";
}

Tile::~Tile() { }

void Tile::update(float deltaTime) { }

void Tile::hit(Entity* hitThis) { }

bool Tile::isSolid() { return solid;  }
bool Tile::isChest() { return chest;  }