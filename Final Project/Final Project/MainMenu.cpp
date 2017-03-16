#include "MainMenu.h"



MainMenu::MainMenu() { }


MainMenu::~MainMenu() { }

void MainMenu::update(float deltaTime) {
	if (up)
		curSelect--;
	else if (down)
		curSelect++;
	curSelect = (curSelect + totalOptions) % totalOptions;
}

int MainMenu::getCurSelect() { return curSelect; }