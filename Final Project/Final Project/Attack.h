#pragma once

#include "Entity.h"
#include "Actor.h"
#include "Tile.h"

class Attack : public Entity {
public:
	Attack(int, int, int, int, Actor*);
	~Attack();

	virtual void hitTile(Tile*);
	virtual void hitActor(Actor*);



	int type;
	bool collidedWithTile = false;
	bool piercing;
	bool melee;
	std::vector<Actor*> attacked;

	void rotation(float);
	
	Actor* source;

	float damage = 1;
};

