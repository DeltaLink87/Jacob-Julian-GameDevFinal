#pragma once

#include "Updatable.h"
#include "Renderable.h"

class Entity : public Updatable, public Renderable {
public:
	Entity(int, int, int, int);
	~Entity();

	bool intersects(sf::RectangleShape);
	virtual void hit(Entity*) = 0;

	void setPostion(sf::Vector2f);

	sf::RectangleShape hitBox;
};

