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

	void renderModel();
	void renderInvMenu();
	void renderCraftMenu();

	sf::View camera;
	sf::Vector2f camPosition;

	sf::View menuCamera;
	sf::RenderTexture modelTexture;
	sf::RenderTexture invMenuTexture;
	sf::RenderTexture craftMenuTexture;
	
	sf::Text textBrush;
	sf::Font font;


	sf::RectangleShape border;
	sf::RectangleShape center;
	sf::RectangleShape divide;

	bool menuOpen = false;

private:
	Model* model;

};

