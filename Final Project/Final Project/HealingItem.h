#pragma once

#include "Item.h"

class HealingItem : public Item {
public:
	HealingItem(std::string, int);
	~HealingItem();

	bool useItem(Entity*);
	Item* getCopy();

protected:
};

