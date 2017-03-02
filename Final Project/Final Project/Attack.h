#pragma once

#include "Entity.h"
#include "Actor.h"

class Attack : public Entity {
public:
	Attack(int, int, int, int, Actor*);
	~Attack();

	void hit(Entity*);

	Actor* source;
};

