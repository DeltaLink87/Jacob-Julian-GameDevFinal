#pragma once

#include "WorldObject.h"

class Renderable : public virtual WorldObject {
public:
	//sf::RectangleShape sprite;

	sf::Sprite sprite;
	std::string textureName = "MissingTexture";
	bool spriteInitialized = false;
	int spriteWidth, spriteHeight;
	sf::Vector2f spritePositionDifference;
	float rotation = 0;
};