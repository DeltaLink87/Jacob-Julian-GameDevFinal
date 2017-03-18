#include "ItemManager.h"
#include <fstream>


ItemManager::ItemManager() {
	std::ifstream filehandle;

	
	filehandle.open("Assets/items.txt");
	for (int i = 1; i < 7; i++) {
		std::string temp;
		filehandle >> temp;
		itemIndex.insert(std::pair<int, std::string>(i, temp));

	}

	

	/*
	Item Index Reference:
		1:  Dagger
		2:  Sword
		3:  Spear
		4:  Rondel (upgraded dagger)
		5:  SinnersScalpel (upgraded Rondel)
		6:  LongSword (upgraded sword)
		7:  BroadSword (upgraded LongSword)
		8:  GreatSword (upgraded BroadSword)
		9:  MasterfulSword (upgraded GreatSword)
		10: Bow
		13: BreastPlate
	*/
	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("Dagger",1)));
	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("Sword", 2)));
	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("Spear", 3)));
	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("Rondel", 4)));
	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("SinnersScalpel", 5)));
	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("LongSword", 6)));
	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("BroadSword", 7)));
	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("GreatSword", 8)));
	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("MasterfulSword", 9)));
	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("Bow", 10)));

	items.insert(std::pair<std::string, Equipment*>("Breast_Plate", new Equipment("Breast_Plate", 13)));


	items.insert(std::pair<std::string, HealingItem*>("Health_Potion", new HealingItem("Health_Potion",2)));
	items.insert(std::pair<std::string, Item*>("Herb", new Item("Herb", 1)));
	items.insert(std::pair<std::string, Item*>("Bottle", new Item("Bottle", 1)));
	items.insert(std::pair<std::string, Item*>("Blade", new Item("Blade", 1)));
	items.insert(std::pair<std::string, Item*>("Wood", new Item("Wood", 1)));
	

}

	ItemManager::~ItemManager() {

	}

Item* ItemManager::getItem(std::string name, int quantity) {
	Item* newItem = items.at(name)->getCopy();
	newItem->quantity = quantity;
	return newItem;
}

int ItemManager::getTotalItems() { return items.size(); }

std::vector<std::string>* ItemManager::getItemList() {
	std::vector<std::string>* list = new std::vector<std::string>;
	//std::cout << items.size() << std::endl;
	for (std::map<std::string, Item*>::iterator i = items.begin(); i != items.end(); i++) {
		//std::cout << "Thing" << std::endl;
		list->push_back(i->first);
	}
	//std::cout << list.size() << std::endl;
	return list;
}

std::map<std::string, Item*>& ItemManager::getAllItems() { return items; }