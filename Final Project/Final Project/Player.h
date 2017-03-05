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

	Equipment* eWeapon;

	
	int maxInventorySize = 5;

	bool craftItem(Item*);

	float attackTimer = 0;
};

