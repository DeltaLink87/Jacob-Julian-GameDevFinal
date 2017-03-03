#include "ItemManager.h"
#include "fstream"

ItemManager::ItemManager() {
	std::ifstream filehandle;

	
	filehandle.open("Assets/items.txt");
	for (int i = 1; i < 7; i++) {
		std::string temp;
		filehandle >> temp;
		itemIndex.insert(std::pair<int, std::string>(i, temp));

	}
	/*
	itemIndex.insert(std::pair<int, std::string>(1, "Dagger"));
	itemIndex.insert(std::pair<int, std::string>(2, "Health Potion"));
	itemIndex.insert(std::pair<int, std::string>(3, "Herb"));
	itemIndex.insert(std::pair<int, std::string>(4, "Bottle"));
	itemIndex.insert(std::pair<int, std::string>(5, "Blade"));
	itemIndex.insert(std::pair<int, std::string>(6, "Wood"));
	*/

	items.insert(std::pair<std::string, Equipment*>("Dagger", new Equipment("Dagger",2)));
	items.insert(std::pair<std::string, UseableItem*>("Health_Potion", new UseableItem("Health_Potion",3)));
	items.insert(std::pair<std::string, Item*>("Herb", new Item("Herb", 1)));
	items.insert(std::pair<std::string, Item*>("Bottle", new Item("Bottle", 1)));
	items.insert(std::pair<std::string, Item*>("Blade", new Item("Blade", 1)));
	items.insert(std::pair<std::string, Item*>("Wood", new Item("Wood", 1)));


}

ItemManager::~ItemManager() {


}