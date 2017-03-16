#pragma once

#include "Item.h"


class UseableItem : public Item {
public:
	UseableItem(std::string, int);
	~UseableItem();

	Item* getCopy();

};
