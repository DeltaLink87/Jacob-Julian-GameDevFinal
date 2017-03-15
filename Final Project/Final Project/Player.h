#pragma once
#include "Actor.h"
#include "Item.h"
#include "Inputable.h"

class Player : public Actor,  public Inputable{
public:
	Player(int, int);
	~Player();

	void update(float);
	void isAttacking(bool);

	int getCurSelected();
	Inventory* getInventory();

	bool craftItem(Item*);

	float attackTimer = 0;
};

