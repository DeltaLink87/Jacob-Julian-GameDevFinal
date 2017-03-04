#pragma once
#include "Actor.h"
#include "Item.h"
#include "Inputable.h"

class Player : public Actor,  public Inputable{
public:
	Player();
	~Player();

	void update(float);
	void isAttacking(bool);

	std::map<std::string, Item*>* getInventory();
	bool craftItem(Item*);

	float attackTimer = 0;
};

