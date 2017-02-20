#pragma once

#include "Controller.h"
#include "Model.h"
#include "Render.h"

#include <SFML/Graphics.hpp>

class Game {
public:
	Game();
	~Game();

	void loop();

	Controller* controller;
	Model* model;
	Render* view;

	sf::Clock gameTime;

};