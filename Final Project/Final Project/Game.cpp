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

	while (view->window.isOpen()) {
		float deltaTime = (float)gameTime.restart().asMilliseconds() / 1000;

		controller->inputs();
		//std::cout << "start" << std::endl;
		model->update(deltaTime);
		//std::cout << "done" << std::endl;
		view->render();
	}
}