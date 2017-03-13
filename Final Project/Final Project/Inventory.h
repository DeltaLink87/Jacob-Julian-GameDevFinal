#pragma once
#include "Item.h"

class Inventory {
public:
	Inventory();
	~Inventory();

	bool addToInventory(Item*);

	//gets an item from inventory and removes it from inventory (int x, int y)
	Item* dropItem(int, int);
	Item* dropRandom();

	//get the current selected item in the quickbar
	Item* getCurSeletected(int);
	//gets an item in inventory (int x, int y)
	Item* getCurSeletected(int, int);
	int getTotalArmourDefence();

	bool contains(std::string);
	bool craft(Item*);

	int getInventorySize();
	int getWidth();
	int getHeight();
	int getArmourSlots();

	void swap(int, int, int, int);

private:
	Item*** items;
	Item** armour;
	int invWidth, invHeight, armourSlots;
	int curX, curY, quickSelect;
	int totalInv = 0;
};

