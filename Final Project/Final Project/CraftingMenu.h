#pragma once

#include "Updatable.h"
#include "ItemManager.h"
#include "Inputable.h"
#include "Player.h"
#include "Inventory.h"

class CraftingMenu : public Inputable{
public:
	CraftingMenu(ItemManager*, Player*);
	~CraftingMenu();

	void update(float);

	sf::RectangleShape selectedBox;

//private:
	int curSelected;
	int totalItems;
	float inputTimer = 0;

	std::vector<std::string> itemNameList;
	std::map<std::string, Item*> itemList;
	bool* canMake;

	ItemManager* itemManager;
	Player* craftingPlayer;
};

