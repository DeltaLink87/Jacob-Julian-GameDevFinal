#pragma once
#include "Equipment.h"

Equipment::Equipment(std::string n, int index) : Item(n, 2) {

	if (index == 1) {
		name = n;
		agility = 1;
		strength = 4;

		recipe.insert(std::pair<std::string, int>("Blade", 1));
		recipe.insert(std::pair<std::string, int>("Wood", 1));
		isWeapon = true;
	}

}


Equipment::Equipment(Item* copy) : Item(2) {



}
