#pragma once
#include "Entity.h"
class Player : public Entity {
public:
	Player();
	~Player();

	void update(float);

	void hit(Entity*);

	sf::Vector2f velocity;

	bool jump = false;
};

