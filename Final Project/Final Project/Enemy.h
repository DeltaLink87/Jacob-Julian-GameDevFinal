#pragma once
#include "Actor.h"
#include "Sound.h"
#include "Loot.h"
#include "MeleeAttack.h"
#include "Projectile.h"
#include "ItemManager.h"
#include "MovementMap.h"

class Enemy : public Actor {
public:
	Enemy();
	Enemy(sf::Vector2f, ItemManager*, MovementMap*);


	~Enemy();

	//updates the enemy
	void update(float);
	//checks if the enemy is close enough to hear a given sound
	void doesHear(Sound*);
	//checks if the enemy can see a player
	void doesSee(Actor*);

	void hitWall(sf::Vector2f, int);
	void overEdge();

	Loot* lootDrop();

	void setPatrolPath(std::vector<sf::Vector2f>*);
	std::vector<sf::Vector2f> path;

protected:
	
	bool containsPoint(sf::Vector2f);
	bool canSeePoint(sf::Vector2f);

	std::vector<sf::Vector2f> patrolPath;
	int curPoint = 0;

	float timer = 0;
	//Keeps track of where the enemy was originally spawned
	sf::Vector2f homePosition;
	//tracks where the last target the enemy saw or heard is
	sf::Vector2f targetLocation, prevTargetLocation;
	MovementMap* pathFinder;
	//std::vector<sf::Vector2f> path;

	bool moving;

	//Time spent attacking
	float attackTime;

	/*  An integer switch used to determine how the enemy AI should behave.
		Current behavior settings are:
		1: Enemy paces back and forth accross its starting point.
		2: Enemy has been alterted by proximity to another object (ie sound or player) and is investigating
		3: Enemy has seen player and is chasing
		4: Enemy is returning to its home position. For when the enemy loses sight of
		   the player or doesn't find anything when investigating a sound.
	*/
	int behaviorState;

	bool jump = false;
};
