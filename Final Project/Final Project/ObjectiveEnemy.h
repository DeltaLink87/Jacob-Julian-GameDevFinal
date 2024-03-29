#pragma once
#include "Enemy.h"
#include "Objective.h"

class ObjectiveEnemy : public Enemy, public Objective {
public:
	ObjectiveEnemy(sf::Vector2f, ItemManager*, MovementMap*);
	~ObjectiveEnemy();

	void remove();
	void reset();
};

