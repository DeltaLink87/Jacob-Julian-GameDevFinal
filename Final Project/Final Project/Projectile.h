#pragma once
#include "Attack.h"

class Projectile : public Attack {
public:
	Projectile(int, int, int, int, sf::Vector2f, Actor*);
	~Projectile();

	void update(float);
};

