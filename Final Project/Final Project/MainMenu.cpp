#include "MainMenu.h"



MainMenu::MainMenu() { }


MainMenu::~MainMenu() { }

void MainMenu::update(float deltaTime) {
	start = false;

	inputTimer -= deltaTime;
	if (inputTimer <= 0) {
		if (up)
			curSelect--;
		else if (down)
			curSelect++;

		if (stageSelect)
			curSelect = (curSelect + totalStages) % totalStages;
		else curSelect = (curSelect + totalOptions) % totalOptions;

		if (select) {
			if (stageSelect) {
				start = true;
			}
			else {
				if (curSelect == 0)
					start = true;
				else if (curSelect == 1) {
					stageSelect = true;
					curSelect = 0;
				}
			}
		}

		if (up || down || select)
			inputTimer = 0.25;
	}
}

int MainMenu::getCurSelect() { return curSelect; }