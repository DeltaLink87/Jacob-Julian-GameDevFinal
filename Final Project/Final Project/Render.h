#pragma once

#include "Model.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Render {
public:
	sf::RenderWindow window;
	int windowWidth, windowHeight;

	Render(Model*);
	~Render();

	void render();

	void renderMenu();

	sf::View camera;

	sf::View menuCamera;
	
	sf::Text textBrush;
	sf::Font font;

	bool menuOpen = false;

private:
	Model* model;

};

