#pragma once
#include "Equipment.h"

Equipment::Equipment(std::string n, int index) : Item(n, 2) {

	if (index == 1) {
		name = n;
		agility = 1;
		strength = 4;
		attack = 1;
		canAssasinate = true;

		recipe.insert(std::pair<std::string, int>("Blade", 1));
		recipe.insert(std::pair<std::string, int>("Wood", 1));
		isWeapon = true;
	}
	else if (index == 2) {
		name = n;
		defence = 2;
		armourType = 2;

		recipe.insert(std::pair<std::string, int>("Iron", 4));
	}

}

Item* Equipment::getCopy() {
	return new Equipment(*this);
}
