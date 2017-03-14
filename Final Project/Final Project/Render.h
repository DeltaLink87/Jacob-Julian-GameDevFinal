#pragma once

#include "Model.h"
#include "AssetManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Render {
public:
	sf::RenderWindow window;
	int windowWidth, windowHeight;

	Render(Model*);
	~Render();

	void initializeRenderable(Renderable*);

	void drawRenderable(sf::RenderTarget&, Renderable*);

	void render();

	void renderModel();
	void renderInvMenu();
	void renderCraftMenu();

	AssetManager manager;

	sf::View camera;
	sf::Vector2f camPosition;

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

