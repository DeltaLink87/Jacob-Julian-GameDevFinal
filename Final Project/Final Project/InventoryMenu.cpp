#include "InventoryMenu.h"



InventoryMenu::InventoryMenu(ItemManager* newItemManager, Player* newPlayer) {
	itemManager = newItemManager;
	menuPlayer = newPlayer;
	curSelected = 0;

	totalItems = 5;

	iMenuTexture.loadFromFile("Assets/Textures/InventoryScreen.png");
	iMenuSprite.setTexture(iMenuTexture);

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

	selectedBox = sf::RectangleShape(sf::Vector2f(iSlotDim.x, iSlotDim.y - 1));
	selectedBox.setFillColor(sf::Color::Transparent);
	selectedBox.setOutlineColor(sf::Color::Green);
	selectedBox.setOutlineThickness(3);
}

InventoryMenu::~InventoryMenu() {
}

void InventoryMenu::update(float deltaTime) {
	//checking if the player has the inventory to craft a given item
	//std::map<std::string, Item*>* playerInventory = menuPlayer->getInventory();
	
	totalItems = menuPlayer->getInventory()->size();

	std::cout << totalItems << std::endl;
	inputTimer -= deltaTime;
	if (inputTimer <= 0) {
		if (up)
			this->curSelected--;
		else if (down)
			this->curSelected++;
		if(totalItems > 0)
			this->curSelected = 1 + ((this->curSelected + 5) % 5);


		if (up || down || select)
			inputTimer = 0.25;
	}
}