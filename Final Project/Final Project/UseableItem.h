#pragma once

#include "Item.h"


class UseableItem : public Item {
public:
	UseableItem();
	UseableItem(std::string, int);
	~UseableItem();

	int health = 0;








};
