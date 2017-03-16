#include "Inventory.h"
#include <string>


Inventory::Inventory(){
	invWidth = 3;
	invHeight = 5;

	curX = 0;
	curY = 0;
	quickSelect = 0;

	items = new Item**[invHeight];
	for (int y = 0; y < invHeight; y++) {
		items[y] = new Item*[invWidth];
		for (int x = 0; x < invWidth; x++) {
			items[y][x] = NULL;
		}
	}

	armourSlots = 4;
	armour = new Item*[armourSlots];
	for (int i = 0; i < armourSlots; i++) {
		armour[i] = NULL;
	}
}

Inventory::~Inventory() { 
	for (int y = 0; y < invHeight; y++) {
		for (int x = 0; x < invWidth; x++) {
			if (items[y][x] != NULL)
				delete items[y][x];
		}
		delete[] items[y];
	}
	delete[] items;

	for (int i = 0; i < armourSlots; i++) {
		if (armour[i] != NULL)
			delete armour[i];
	}
	delete[] armour;
}

bool Inventory::addToInventory(Item* newItem) {
	int freeX = -1, freeY = -1;
	for (int x = 0; x < invWidth; x++) {
		for (int y = 0; y < invHeight; y++) {
			if (items[y][x] != NULL) {
				if (items[y][x]->name.compare(newItem->name) == 0) {
					items[y][x]->quantity += newItem->quantity;
					delete newItem;
					return true;
				}
			}
			else if (freeX == -1 && freeY == -1) {
				freeX = x;
				freeY = y;
			}
		}
	}

	if (freeX != -1 && freeY != -1) {
		items[freeY][freeX] = newItem;
		totalInv++;
		return true;
	}

	return false;
}

bool Inventory::addToInventory(Item* newItem, int x, int y) {
	if (x == -1) {
		if (armour[y] == NULL && newItem->armourType - 1 == y){
			armour[y] = newItem;
			totalInv++;
			return true;
		}
	}
	else if (items[y][x] == NULL) {
		items[y][x] = newItem;
		totalInv++;
		return true;
	}
	return addToInventory(newItem);
}

Item* Inventory::dropItem(int x, int y) {
	Item* droppedItem = NULL;
	if (x == -1) {
		droppedItem = armour[y];
		armour[y] = NULL;
	}
	else {
		droppedItem = items[y][x];
		items[y][x] = NULL;
	}

	if (droppedItem != NULL)
		totalInv--;

	return droppedItem;
}

Item* Inventory::dropRandom() {
	//Item* droppedItem;
	//if (totalInv > 0)
	//std::cout << totalInv << std::endl;
	if (totalInv == 0)
		return NULL;

	int selectedItem = rand() % totalInv, counter = 0;
	//std::cout << selectedItem << std::endl;

	for (int y = 0; y < invHeight; y++) {
		for (int x = 0; x < invWidth; x++) {
			if (items[y][x] != NULL) {
				if (counter == selectedItem) {
					Item* droppedItem = items[y][x];
					items[y][x] = NULL;
					totalInv--;
					return droppedItem;
				}
				counter++;
			}
		}
	}

	for (int y = 0; y < armourSlots; y++) {
		if (armour[y] != NULL) {
			if (counter == selectedItem) {
				Item* droppedItem = armour[y];
				armour[y] = NULL;
				totalInv--;
				return droppedItem;
			}
			counter++;
		}
	}
	//std::cout << "Not found" << std::endl;
	return NULL;
}

bool Inventory::contains(std::string itemName, int quantity) {
	for (int x = 0; x < invWidth; x++) {
		for (int y = 0; y < invHeight; y++) {
			if (items[y][x] != NULL) {
				if (items[y][x]->name.compare(itemName) == 0) {
					quantity -= items[y][x]->quantity;
					if (quantity <= 0)
						return true;
				}
			}
		}
	}
	return false;
}

bool Inventory::craft(Item* item) {
	for (std::map<std::string, int>::iterator i = item->recipe.begin(); i != item->recipe.end(); i++) {
		bool found = contains(i->first, i->second);
		if (!found) return false;
	}

	for (std::map<std::string, int>::iterator i = item->recipe.begin(); i != item->recipe.end(); i++) {
		bool found = false;
		int totalNeeded = i->second;
		for (int x = 0; x < invWidth && !found; x++) {
			for (int y = 0; y < invHeight && !found; y++) {
				if (items[y][x] != NULL) {
					if (items[y][x]->name.compare(i->first) == 0) {
						int quantity = items[y][x]->quantity;
						items[y][x]->quantity -= totalNeeded;
						totalNeeded -= quantity;

						if (items[y][x]->quantity <= 0) {
							delete items[y][x];
							items[y][x] = NULL;
						}

						if (totalNeeded <= 0)
							found = true;
					}
				}
			}
		}
	}

	addToInventory(item);
	return true;
}

void Inventory::swap(int x1, int y1, int x2, int y2) {
	Item* item1;
	Item* item2;
	if (x1 == -1)	item1 = armour[y1];
	else item1 = items[y1][x1];
	if (x2 == -1)	item2 = armour[y2];
	else item2 = items[y2][x2];

	if (x1 == -1 && item2 != NULL)
		if (item2->armourType - 1 != y1)	
			return;
	if (x2 == -1 && item1 != NULL) 
		if (item1->armourType - 1 != y2)	
			return;

	if (x1 == -1)	armour[y1] = item2;
	else items[y1][x1] = item2;
	if (x2 == -1)	armour[y2] = item1;
	else items[y2][x2] = item1;
}

int Inventory::getTotalArmourDefence() {
	int total = 0;
	for (int i = 0; i < armourSlots; i++)
		if (armour[i] != NULL)
			total += armour[i]->defence;
	return total;
}

Item* Inventory::getCurSeletected(int i) { return items[i][0]; }
Item* Inventory::getCurSeletected(int x, int y) {
	if (x == -1)
		return armour[y];
	else return items[y][x]; 
}
int Inventory::getInventorySize() { return totalInv; }
int Inventory::getWidth() { return invWidth; }
int Inventory::getHeight() { return invHeight; }
int Inventory::getArmourSlots() { return armourSlots; }