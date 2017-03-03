#pragma once

#include "Entity.h"
#include "Actor.h"
#include "Tile.h"

class Attack : public Entity {
public:
	Attack(int, int, int, int, Actor*);
	~Attack();

	void hitTile(Tile*);
	void hitActor(Actor*);

	Actor* source;

	float damage = 1;
};

