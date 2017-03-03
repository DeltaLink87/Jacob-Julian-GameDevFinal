#pragma once

#include "UseableItem.h"

UseableItem::UseableItem(std::string n, int index) : Item(n,3) {

	if (index == 2) {
		name = n;
		health = 5;

		recipe.insert(std::pair<std::string, int>("Herb", 1));
		recipe.insert(std::pair<std::string, int>("Bottle", 1));

	}


}