#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Windows.h>
#include <iostream>
#include "Game.h"

Game::Game() {
	std::srand(std::time(0));

	model = new Model();
	view = new Render(model);
	controller = new Controller(model, view);
}

Game::~Game() {
	//no destructor
}

void Game::loop() {
	gameTime.restart();
	int framesSkipped = 0;
	float timeForLoop = 1000 / 30;
	bool start = false;

	while (view->window.isOpen()) {
		float deltaTime = (float)gameTime.restart().asMilliseconds() / 1000;

		//capping deltaTime so that it doesn't cause problems in the game
		if (deltaTime > timeForLoop / 1000 * 2)
			deltaTime = timeForLoop / 1000 * 2;

		//checking if the level is loading and stopping the game from doing anything if it is
		if (model->loadingLevel) {
			deltaTime = 0;
			model->loadingLevel = false;
		}

		//checking if the game has started, to prevent bug due to deltaTime being to large from things loading
		if (start) {
			controller->inputs();
			//std::cout << "start" << std::endl;
			model->update(deltaTime);
			//std::cout << gameTime.getElapsedTime().asMilliseconds() << std::endl;
			if (deltaTime > timeForLoop / 1000)
				std::cout << deltaTime << std::endl;
		}
		//checking to skip this frame
		if (gameTime.getElapsedTime().asMilliseconds() < timeForLoop || framesSkipped > 2 || model->loadingLevel) {
			view->render();
			framesSkipped = 0;
		}
		else {
			framesSkipped++;
			std::cout << framesSkipped << " frames skipped" << std::endl;
		}

		//checking if the game is running smoothly now
		if (gameTime.getElapsedTime().asMilliseconds() < timeForLoop)
			start = true;
	}
}