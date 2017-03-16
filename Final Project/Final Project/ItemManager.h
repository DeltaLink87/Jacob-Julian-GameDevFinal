#pragma once
#include "Item.h"
#include "UseableItem.h"
#include "HealingItem.h"
#include "Equipment.h"
#include "fstream"

class ItemManager {
public:
	ItemManager();
	~ItemManager();

	std::map<int, std::string> itemIndex;

	//std::string** itemIndex = { "Dagger", "Health Potion" };

	Item* getItem(std::string, int);
	int getTotalItems();
	std::vector<std::string>* getItemList();
	std::map<std::string, Item*>& getAllItems();
	



	



private:
	std::map<std::string, Item*> items;
	//std::map<std::string, Equipment*> equipment;
	//std::map<std::string, UseableItem*> consumables;

};