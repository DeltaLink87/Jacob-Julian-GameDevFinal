#pragma once

#include "Item.h"


class Equipment: public Item {
public:
	Equipment();
	Equipment(std::string, int);
	Equipment(Item*);

	~Equipment();

	Item* getEquipment(std::string);

	Item* getCopy();


	bool isWeapon = false;
	bool isEquipped = false;

	int health = 0;
	int strength = 0;
	int intelligence = 0;
	int resistance = 0;
	int agility = 0;

};
