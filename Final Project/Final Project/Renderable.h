#pragma once

#include "WorldObject.h"

class Renderable : public virtual WorldObject {
public:
/* --TEMP--

	sf::RectangleShape sprite;
	//Not calling them "sprite" so that when we switch to stop using the RectangleShape, ctrl+f "sprite" will only turn up things that need to be changed.
	sf::Texture textureOfVisualRepresentation;
	sf::Sprite visualRepresentation;
  
  */

	bool spritePositionSet = false;

	sf::Sprite sprite;
	std::string textureName = "MissingTexture";
	bool spriteInitialized = false, displaySprite = true;
	int spriteWidth, spriteHeight;
	sf::Vector2f spritePositionDifference;
	float spriteRotation = 0;
};