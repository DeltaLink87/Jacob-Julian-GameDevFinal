#pragma once
#include "Inputable.h"
class MainMenu : public Inputable {
public:
	MainMenu();
	~MainMenu();

	void update(float);

	int getCurSelect();

	sf::Sprite titleCardSprite;
	sf::Sprite optionSprite[2];

	bool start = false;
	int totalStages = 0;
	bool stageSelect = false;

private:
	int curSelect = 0;
	int totalOptions = 2;
	float inputTimer = 0;
};

