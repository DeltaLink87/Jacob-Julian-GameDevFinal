#pragma once
#include "WorldObject.h"

class Objective : virtual public WorldObject{
public:
	bool isComplete() { return complete; }
	virtual void reset() = 0;

	sf::Sprite objFlagSprite;
	sf::Vector2f flagPosDif;
	std::string flagTextureName = "ObjectiveFlag";
	int flagWidth = 20, flagHeight = 20;
	bool initialized = false;

protected:
	bool complete = false;
};