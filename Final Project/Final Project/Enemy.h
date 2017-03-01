#pragma once
#include "Entity.h"
class Enemy : public Entity {
public:
	Enemy();
	Enemy(sf::Vector2f);
	~Enemy();

	void update(float);

	void hit(Entity*);

	sf::Vector2f velocity;

	//Keeps track of where the enemy was originally spawned
	sf::Vector2f homePosition;


	/*  An integer switch used to determine how the enemy AI should behave.
		Current behavior settings are:
		1: Enemy paces back and forth accross its starting point.
		2: Enemy has been alterted by proximity to another object (ie sound or player)
		3: Enemy is returning to its home position. For when the enemy loses sight of
		   the player or doesn't find anything when investigating a sound.
		
	*/
	int behaviorState;

	bool jump = false;
};

