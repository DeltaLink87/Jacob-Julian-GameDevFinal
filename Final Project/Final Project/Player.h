#pragma once
#include "Actor.h"
#include "Item.h"
class Player : public Actor {
public:
	Player();
	~Player();

	void update(float);

	void hit(Entity*);

	bool jump = false, moveSlow = false, moveFast = false;// , attack = false;
	bool up = false , down = false, left = false, right = false;

	


	sf::Vector2f looking;
};

