#pragma once
#include "Entity.h"
class Enemy : public Entity {
public:
	Enemy();
	~Enemy();

	void update(float);

	void hit(Entity*);

	void update(sf::Time, sf::Vector2f);


	sf::Vector2f velocity;

	//Used to store where the enemy was originally placed
	//for when the player disengages and the enemy needs to return
	//to its original position to return to its natural behavior
	sf::Vector2f homePosition; 

	//An integer switch used to determine how the enemy AI should behave
	/* Current behavior settings are:
		1: Enemy paces back and forth accross its starting point
		2: Enemy has been alerted by proximity to another object (ie sound object or player)
		3: For when the enemy loses sight of the player or doesn't find anything when
		   investigating a sound. Enemy is returning to its homePosition.	
	*/
	int behaviorState;

	bool jump = false;
};

