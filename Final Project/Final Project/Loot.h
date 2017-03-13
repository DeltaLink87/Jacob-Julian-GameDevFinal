#pragma once

#include "Entity.h"
#include "Item.h"

class Loot : public Entity
{
public:
	Loot(int, int, int, int, Item*);
	~Loot();

	void update(float);

	Item* getDrop();

protected:
	Item* itemDrop;
};

