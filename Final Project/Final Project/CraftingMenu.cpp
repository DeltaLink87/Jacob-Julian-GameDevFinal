#include "CraftingMenu.h"



CraftingMenu::CraftingMenu(ItemManager* newItemManager, Player* newPlayer) {
	itemManager = newItemManager;
	craftingPlayer = newPlayer;
	this->curSelected = 0;

	std::vector<std::string>* tempList = itemManager->getItemList();
	//std::cout << tempList->size() << std::endl;
	for (std::vector<std::string>::iterator i = tempList->begin(); i != tempList->end(); i++) {
		//std::cout << *i << std::endl;
		if (itemManager->getItem(*i, 1)->getID() != 1) {
			itemNameList.push_back(*i);
			itemList.insert(std::pair<std::string, Item*>(*i, itemManager->getItem(*i, 1)));
		}
	}
	totalItems = itemList.size();
	//std::cout << totalItems << std::endl;

	canMake = new bool[totalItems];

	selectedBox = sf::RectangleShape(sf::Vector2f(130, 70));
	selectedBox.setFillColor(sf::Color::Transparent);
	selectedBox.setOutlineColor(sf::Color::Black);
	selectedBox.setOutlineThickness(4);
}

CraftingMenu::~CraftingMenu(){ 
	delete[] canMake;
}

void CraftingMenu::openMenu() {
	//checking if the player has the inventory to craft a given item
	Inventory* playerInventory = craftingPlayer->getInventory();
	int counter = 0;
	for (std::map<std::string, Item*>::iterator i = itemList.begin(); i != itemList.end(); i++) {
		bool hasRequirements = true;
		for (std::map<std::string, int>::iterator r = (*i).second->recipe.begin(); r != (*i).second->recipe.end() && hasRequirements; r++) {
			if (!playerInventory->contains(r->first, r->second))
				hasRequirements = false;
			//std::cout << (playerInventory->count((*r).first) == 0) << std::endl;
		}
		//std::cout << (*i).second->recipe.size() << std::endl;
		canMake[counter] = hasRequirements;
		//std::cout << canMake[counter] << std::endl;
		counter++;
	}
}

void CraftingMenu::update(float deltaTime) {
	//checking if the player can input a new input(to slow down input)
	inputTimer -= deltaTime;
	if (inputTimer <= 0) {
		//moving cursor up and down
		if (up)
			this->curSelected--;
		else if (down)
			this->curSelected++;
		this->curSelected = (this->curSelected + totalItems) % totalItems;
		//crafting an item if selected
		if (select && canMake[this->curSelected]) {
			craftingPlayer->craftItem(itemList.at(itemNameList.at(this->curSelected))->getCopy());
			openMenu();
		}
		//reseting input timer if an input was put in
		if (up || down || select)
			inputTimer = 0.25;
	}
}

void CraftingMenu::setPlayer(Player* newPlayer) { craftingPlayer = newPlayer; }