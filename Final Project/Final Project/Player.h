#pragma once
#include "Entity.h"
class Player : public Entity {
public:
	Player();
	~Player();

	void update(float);

	sf::Vector2f velocity;
};

