#pragma once
#include "Attack.h"

class MeleeAttack : public Attack {
public:
	MeleeAttack(int, int, int, int, float, Actor*);
	~MeleeAttack();

	void update(float);

	float duration = 1.0;
	float direction;
};

