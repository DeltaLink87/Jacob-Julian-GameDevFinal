#include "CraftingMenu.h"



CraftingMenu::CraftingMenu(ItemManager* newItemManager, Player* newPlayer) {
	itemManager = newItemManager;
	craftingPlayer = newPlayer;
	this->curSelected = 0;

	std::vector<std::string>* tempList = itemManager->getItemList();
	//std::cout << tempList->size() << std::endl;
	for (std::vector<std::string>::iterator i = tempList->begin(); i != tempList->end(); i++) {
		if (itemManager->getItem(*i)->id != 1) {
			itemNameList.push_back(*i);
			itemList.insert(std::pair<std::string, Item*>(*i, itemManager->getItem(*i)));
		}
	}
	totalItems = itemList.size();
	//std::cout << totalItems << std::endl;

	canMake = new bool[totalItems];

	selectedBox = sf::RectangleShape(sf::Vector2f(130, 70));
	selectedBox.setFillColor(sf::Color::Transparent);
	selectedBox.setOutlineColor(sf::Color::White);
	selectedBox.setOutlineThickness(4);
}

CraftingMenu::~CraftingMenu() {
	delete[] canMake;
}

void CraftingMenu::update(float deltaTime) {
	//checking if the player has the inventory to craft a given item
	Inventory* playerInventory = craftingPlayer->getInventory();
	int counter = 0;
	for (std::map<std::string, Item*>::iterator i = itemList.begin(); i != itemList.end(); i++) {
		bool hasRequirements = true;
		for (std::map<std::string, int>::iterator r = (*i).second->recipe.begin(); r != (*i).second->recipe.end() && hasRequirements; r++) {
			if (!playerInventory->contains((*r).first))
				hasRequirements = false;
			//std::cout << (playerInventory->count((*r).first) == 0) << std::endl;
		}
		//std::cout << (*i).second->recipe.size() << std::endl;
		canMake[counter] = hasRequirements;
		//std::cout << canMake[counter] << std::endl;
		counter++;
	}

	inputTimer -= deltaTime;
	if (inputTimer <= 0) {
		if (up)
			this->curSelected--;
		else if (down)
			this->curSelected++;
		this->curSelected = (this->curSelected + totalItems) % totalItems;

		if (select && canMake[this->curSelected]) {
			craftingPlayer->craftItem(itemList.at(itemNameList.at(this->curSelected)));
		}

		if (up || down || select)
			inputTimer = 0.25;
	}
}