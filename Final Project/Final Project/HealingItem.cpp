#include "HealingItem.h"



HealingItem::HealingItem(std::string n, int index) : Item(n, 3) {
	if (index == 2) {
		name = n;
		amountToHeal = 10;
		durLossPerUse = 1;

		recipe.insert(std::pair<std::string, int>("Herb", 1));
		recipe.insert(std::pair<std::string, int>("Bottle", 1));

	}
}


HealingItem::~HealingItem(){ }

bool HealingItem::useItem(Entity* usedBy) {
	std::cout << "healing" << std::endl;
	usedBy->HealHealth(amountToHeal);
	return true;
}

Item* HealingItem::getCopy() {
	return new HealingItem(*this);
}