#pragma once

#include "WorldObject.h"

class Renderable : public virtual WorldObject {
public:
	sf::RectangleShape sprite;
};