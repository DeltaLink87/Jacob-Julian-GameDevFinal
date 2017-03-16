#pragma once
#include "Inputable.h"
class MainMenu : public Inputable {
public:
	MainMenu();
	~MainMenu();

	void update(float);

	int getCurSelect();

	sf::Sprite titleCardSprite;
	sf::Sprite optionSprite[1];

private:
	int curSelect = 0;
	int totalOptions = 1;
	float inputTimer = 0;
};

