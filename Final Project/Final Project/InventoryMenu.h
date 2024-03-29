#pragma once

#include "Updatable.h"
#include "ItemManager.h"
#include "Inputable.h"
#include "Player.h"

class InventoryMenu : public Inputable {
public:
	InventoryMenu(ItemManager*, Player*);
	~InventoryMenu();

	void update(float);

	sf::RectangleShape cursorBox;
	sf::RectangleShape selectedBox;

	//private:
	int getCurX();
	int getCurY();
	int getSelectedX();
	int getSelectedY();

	void setPlayer(Player*);

	sf::Sprite iMenuSprite;
	sf::Texture iMenuTexture;

	//Index of the top left pixel of the first inventory slot
	sf::Vector2f iSlotStart = sf::Vector2f(289.0, 56.0);
	//Dimension of individual inventory slots (right side of menu)
	sf::Vector2f iSlotDim = sf::Vector2f(51.0, 55.0);
	//Size of the gaps between slots
	sf::Vector2f iSlotOff = sf::Vector2f(3.0, 3.0);

	//Index of the top left pixel of the weapon slot
	sf::Vector2f wSlotStart = sf::Vector2f(176.0, 17.0);
	//Dimension of the weapon slot
	sf::Vector2f wSlotDim = sf::Vector2f(43.0, 33.0);

private:
	int curX = 0, curY = 0;
	int selectedX = -2, selectedY = -2;
	int totalItems;
	float inputTimer = 0;

	ItemManager* itemManager;
	Player* menuPlayer;
};

