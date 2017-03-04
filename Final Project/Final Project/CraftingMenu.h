#pragma once

#include "Updatable.h"
#include "ItemManager.h"

class CraftingMenu {
public:
	CraftingMenu(ItemManager*);
	~CraftingMenu();

	void update(float);

	bool up, down, left, right, select;

//private:
	int curSelected;
	int totalItems;

	std::vector<std::string> itemNameList;
	std::map<std::string, Item*> itemList;

	ItemManager* itemManager;
};

