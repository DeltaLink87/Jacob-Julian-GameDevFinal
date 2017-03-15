#pragma once
#include "Attack.h"

class MeleeAttack : public Attack {
public:

	enum {	DAGGER = 1, SWORD = 2 };

	MeleeAttack(int, int, int, int, float, Actor*);
	MeleeAttack(int, int, int, int, float, Actor*, int);
	~MeleeAttack();

	void update(float);
	void hitTile(Tile*);

	float duration = 1.0;
	float direction;

	bool thrust;

	sf::Vector2f anchor;
	
	float attackMotion;

	float pi = 3.14159;

};

