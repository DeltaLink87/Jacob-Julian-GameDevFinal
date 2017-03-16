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
	void renderUI();
	void renderInvMenu();
	void renderCraftMenu();
	void renderMainMenu();
	void renderWin();

	AssetManager manager;

	sf::View camera;
	sf::Vector2f camPosition;

	sf::RenderTexture modelTexture;
	sf::RenderTexture invMenuTexture;
	sf::RenderTexture craftMenuTexture;
	sf::RenderTexture UITexture;
	sf::RenderTexture mainMenuTexture;

	sf::Text textBrush;
	sf::Font font;

	sf::RectangleShape border;
	sf::RectangleShape center;
	sf::RectangleShape divide;

	bool menuOpen = false;

	float screenAlpha = 0;
private:
	Model* model;

};

