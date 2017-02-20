#pragma once

#include "Model.h"

#include <SFML/Graphics.hpp>

class Render {
public:
	sf::RenderWindow window;
	int windowWidth, windowHeight;

	Render(Model*);
	~Render();

	void render();

private:
	Model* model;
};

