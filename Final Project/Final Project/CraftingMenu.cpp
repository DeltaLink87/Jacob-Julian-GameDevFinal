#include "CraftingMenu.h"



CraftingMenu::CraftingMenu(ItemManager* newItemManager) {
	itemManager = newItemManager;
	curSelected = 0;

	std::vector<std::string>* tempList = itemManager->getItemList();
	std::cout << tempList->size() << std::endl;
	for (std::vector<std::string>::iterator i = tempList->begin(); i != tempList->end(); i++) {
		if (itemManager->getItem(*i)->id != 1) {
			itemNameList.push_back(*i);
			itemList.insert(std::pair<std::string, Item*>(*i, itemManager->getItem(*i)));
		}
	}
	totalItems = tempList->size();
	std::cout << totalItems << std::endl;
}

CraftingMenu::~CraftingMenu() { }

void CraftingMenu::update(float deltaTime) {
	if (up)
		curSelected--;
	else if (down)
		curSelected++;
	curSelected = (curSelected + totalItems) % totalItems;
}