#include "Inventory.h"
#include <string>


Inventory::Inventory(){
	invWidth = 3;
	invHeight = 5;

	curX = 0;
	curY = 0;
	quickSelect = 0;

	//creating inventory slots
	items = new Item**[invHeight];
	for (int y = 0; y < invHeight; y++) {
		items[y] = new Item*[invWidth];
		for (int x = 0; x < invWidth; x++) {
			items[y][x] = NULL;
		}
	}

	//creating armour slots
	armourSlots = 4;
	armour = new Item*[armourSlots];
	for (int i = 0; i < armourSlots; i++) {
		armour[i] = NULL;
	}
}

Inventory::~Inventory() { 
	//deallocating inventory
	for (int y = 0; y < invHeight; y++) {
		for (int x = 0; x < invWidth; x++) {
			if (items[y][x] != NULL)
				delete items[y][x];
		}
		delete[] items[y];
	}
	delete[] items;

	//deallocating armour
	for (int i = 0; i < armourSlots; i++) {
		if (armour[i] != NULL)
			delete armour[i];
	}
	delete[] armour;
}

bool Inventory::addToInventory(Item* newItem) {
	if (newItem == NULL)	//checking that item is given
		return false;

	int freeX = -1, freeY = -1;
	//loops through all inventory to find same item to stack on or find first free slot
	for (int x = 0; x < invWidth; x++) {
		for (int y = 0; y < invHeight; y++) {
			if (items[y][x] != NULL) {	//checking if item exists and is same as item to add
				if (items[y][x]->getName().compare(newItem->getName()) == 0) {
					items[y][x]->addQuantity(newItem->getQuantity());
					delete newItem;
					return true;
				}
			}
			else if (freeX == -1 && freeY == -1) {	//marking this as the first free slot
				freeX = x;
				freeY = y;
			}
		}
	}

	//if no matching item found, setting first free spot to item (if free spot found)
	if (freeX != -1 && freeY != -1) {
		items[freeY][freeX] = newItem;
		totalInv++;
		return true;
	}

	return false;
}

bool Inventory::addToInventory(Item* newItem, int x, int y) {
	if (newItem == NULL)	//checking that item is given
		return false;

	if (x == -1) {	//if noted to put in armour slot, put in the armour array if armour for that slot
		if (armour[y] == NULL && newItem->getArmourType() - 1 == y){
			armour[y] = newItem;
			totalInv++;
			return true;
		}
	}
	//else if not to be put in armour slots, put in given slot if slot empty
	else if (items[y][x] == NULL) {
		items[y][x] = newItem;
		totalInv++;
		return true;
	}
	//else add to first avaliable spot
	return addToInventory(newItem);
}

Item* Inventory::dropItem(int x, int y) {
	Item* droppedItem = NULL;
	//getting from armour array if given
	if (x == -1) {
		droppedItem = armour[y];
		armour[y] = NULL;
	}
	//else getting from regular inventory
	else {
		droppedItem = items[y][x];
		items[y][x] = NULL;
	}

	//if actual item gotten, decreasing items in inventory
	if (droppedItem != NULL)
		totalInv--;

	return droppedItem;	//returning item
}

Item* Inventory::dropRandom() {
	//Item* droppedItem;
	//if (totalInv > 0)
	//std::cout << totalInv << std::endl;
	if (totalInv == 0)	//checking for inventory
		return NULL;

	//randomly selecting an item from inventory
	int selectedItem = rand() % totalInv, counter = 0;
	//std::cout << selectedItem << std::endl;

	//looping until found the selected item
	for (int y = 0; y < invHeight; y++) {
		for (int x = 0; x < invWidth; x++) {
			if (items[y][x] != NULL) {
				if (counter == selectedItem) {
					//removing item from array when found and returning it
					Item* droppedItem = items[y][x];
					items[y][x] = NULL;
					totalInv--;
					return droppedItem;
				}
				counter++;
			}
		}
	}

	//if not found in regular inventory, checking armour slots
	for (int y = 0; y < armourSlots; y++) {
		if (armour[y] != NULL) {
			if (counter == selectedItem) {
				//removing item from array when found and returning it
				Item* droppedItem = armour[y];
				armour[y] = NULL;
				totalInv--;
				return droppedItem;
			}
			counter++;
		}
	}
	
	//return null if not found
	return NULL;
}

bool Inventory::contains(std::string itemName, int quantity) {
	//looping until finding the given item
	for (int x = 0; x < invWidth; x++) {
		for (int y = 0; y < invHeight; y++) {
			if (items[y][x] != NULL) {
				if (items[y][x]->getName().compare(itemName) == 0) {
					//subtracting the quantity of the item to check if there is enough of that item in inventory
					quantity -= items[y][x]->getQuantity();
					if (quantity <= 0)
						return true;
				}
			}
		}
	}

	//return false if not found
	return false;
}

bool Inventory::craft(Item* item) {
	//checking if inventory has the required items, returns false if not
	for (std::map<std::string, int>::iterator i = item->recipe.begin(); i != item->recipe.end(); i++) {
		bool found = contains(i->first, i->second);
		if (!found) return false;
	}

	//removing all items required to create given item
	for (std::map<std::string, int>::iterator i = item->recipe.begin(); i != item->recipe.end(); i++) {
		bool found = false;
		int totalNeeded = i->second;
		for (int x = 0; x < invWidth && !found; x++) {
			for (int y = 0; y < invHeight && !found; y++) {
				if (items[y][x] != NULL) {
					if (items[y][x]->getName().compare(i->first) == 0) {
						//checking that there is enough of the item in this stack to create the new item
						int quantity = items[y][x]->getQuantity();
						items[y][x]->addQuantity(-totalNeeded);
						totalNeeded -= quantity;

						//if this stack of the used item is depleted, remove from inventory
						if (items[y][x]->getQuantity() <= 0) {
							delete items[y][x];
							items[y][x] = NULL;
						}

						//check if the required amount of the needed item has been found
						if (totalNeeded <= 0)
							found = true;
					}
				}
			}
		}
	}

	//adding this item to inventory
	addToInventory(item);
	return true;
}

void Inventory::swap(int x1, int y1, int x2, int y2) {
	Item* item1;
	Item* item2;
	//checking if either item is in armour and getting there pointer addresses
	if (x1 == -1)	item1 = armour[y1];
	else item1 = items[y1][x1];
	if (x2 == -1)	item2 = armour[y2];
	else item2 = items[y2][x2];

	//checking that the items can be swapped (one slot may be in armour)
	if (x1 == -1 && item2 != NULL)	//checking that item2 can go into the spot item1 is in
		if (item2->getArmourType() - 1 != y1)	
			return;
	if (x2 == -1 && item1 != NULL)	//checking that item1 can go into the spot item2 is in
		if (item1->getArmourType() - 1 != y2)
			return;

	//swapping items in the array
	if (x1 == -1)	armour[y1] = item2;
	else items[y1][x1] = item2;
	if (x2 == -1)	armour[y2] = item1;
	else items[y2][x2] = item1;
}

//adding up the total defence of the armour equipped in this inventory
int Inventory::getTotalArmourDefence() {
	int total = 0;
	for (int i = 0; i < armourSlots; i++)
		if (armour[i] != NULL)
			total += armour[i]->getDefence();
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