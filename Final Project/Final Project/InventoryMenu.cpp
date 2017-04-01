#include "InventoryMenu.h"



InventoryMenu::InventoryMenu(ItemManager* newItemManager, Player* newPlayer) {
	itemManager = newItemManager;
	menuPlayer = newPlayer;
	curX = 0;
	curY = 0;

	totalItems = 5;

	iMenuTexture.loadFromFile("Assets/Textures/InventoryScreen.png");
	iMenuSprite.setTexture(iMenuTexture);

	cursorBox = sf::RectangleShape(sf::Vector2f(iSlotDim.x, iSlotDim.y - 1));
	cursorBox.setFillColor(sf::Color::Transparent);
	cursorBox.setOutlineColor(sf::Color::Green);
	cursorBox.setOutlineThickness(3);
  
	selectedBox = sf::RectangleShape(sf::Vector2f(iSlotDim.x, iSlotDim.y - 1));
	selectedBox.setFillColor(sf::Color::Transparent);
	selectedBox.setOutlineColor(sf::Color::Yellow);
	selectedBox.setOutlineThickness(3);
}

InventoryMenu::~InventoryMenu() {
}

void InventoryMenu::update(float deltaTime) {
	//checking if the player has the inventory to craft a given item
	//std::map<std::string, Item*>* playerInventory = menuPlayer->getInventory();
	

	totalItems = menuPlayer->getInventory()->getInventorySize();

	inputTimer -= deltaTime;
	if (inputTimer <= 0) {
		if (up) {
			this->curY--;
		}
		else if (down) {
			this->curY++;
		}

		if (left) {
			this->curX--;
		}
		else if (right) {
			this->curX++;
		}

		if (curY < 0) {
			if (curX == -1)
				curY = menuPlayer->getInventory()->getArmourSlots() - 1;
			else curY = menuPlayer->getInventory()->getHeight() - 1;
		}
		else if (curX <= -1 && curY >= menuPlayer->getInventory()->getArmourSlots())
			curY = 0;
		else if (curY >= menuPlayer->getInventory()->getHeight())
			curY = 0;

		if (curY >= menuPlayer->getInventory()->getArmourSlots() && curX < 0)
			curX = menuPlayer->getInventory()->getWidth() - 1;
		else if (curY < menuPlayer->getInventory()->getArmourSlots() && curX < -1)
			curX = menuPlayer->getInventory()->getWidth() - 1;
		else if (curX >= menuPlayer->getInventory()->getWidth()) {
			if (curY >= menuPlayer->getInventory()->getArmourSlots())
				curX = 0;
			else if (curY < menuPlayer->getInventory()->getArmourSlots())
				curX = -1;
		}

		if (select) {
			if (selectedX == -2 && selectedY == -2) {
				if (menuPlayer->getInventory()->getCurSeletected(curX, curY) != NULL) {
					selectedX = curX;
					selectedY = curY;
				}
			}
			else  {
				if (selectedX != curX || selectedY != curY)
					menuPlayer->getInventory()->swap(curX, curY, selectedX, selectedY);
				selectedX = -2;
				selectedY = -2;
			}
		}

		if (up || down || left || right || select)
			inputTimer = 0.25;
	}
}

int InventoryMenu::getCurX() { return curX; }
int InventoryMenu::getCurY() { return curY; }
int InventoryMenu::getSelectedX() { return selectedX; }
int InventoryMenu::getSelectedY() { return selectedY; }
void InventoryMenu::setPlayer(Player* newPlayer) { menuPlayer = newPlayer; }