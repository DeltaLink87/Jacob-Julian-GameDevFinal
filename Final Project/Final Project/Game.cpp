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

		if (model->loadingLevel) {
			deltaTime = 0;
			model->loadingLevel = false;
		}

		if (start) {
			controller->inputs();
			//std::cout << "start" << std::endl;
			model->update(deltaTime);
			//std::cout << gameTime.getElapsedTime().asMilliseconds() << std::endl;
		}
		if (gameTime.getElapsedTime().asMilliseconds() < timeForLoop || framesSkipped > 2 || model->loadingLevel) {
			view->render();
			framesSkipped = 0;
		}
		else framesSkipped++;

		if (gameTime.getElapsedTime().asMilliseconds() < timeForLoop)
			start = true;
	}
}