#pragma once

#include <SFML\Graphics.hpp>

class Inputable {
public:
	bool jump = false, moveSlow = false, moveFast = false, pressAttack = false, mouseLessAttack = false;
	bool up = false, down = false, left = false, right = false;
	bool select = false, craftingMenu = false, inventoryMenu = false;
	bool hasWeaponEquipped = false;
	bool mouse2 = false;
	sf::Vector2f looking;
	int scroll = 0;
	bool scrollRight = false, scrollLeft = false;

	float inputTimer = 0;

	bool toMainMenu = false;
};