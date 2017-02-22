#include "Render.h"


Render::Render(Model* newModel){
	model = newModel;

	windowWidth = 800;
	windowHeight = 600;

	window.create(sf::VideoMode(windowWidth, windowHeight), "LIVE DEMO");

	window.setFramerateLimit(30);

	camera.setSize(sf::Vector2f(windowWidth, windowHeight));
}

Render::~Render(){ }

void Render::render() {
	sf::Vector2f camPosition = model->player.position;
	if (camPosition.x < windowWidth / 2)
		camPosition.x = windowWidth / 2;
	else if (camPosition.x > model->mapWidth * model->tileSize - windowWidth / 2)
		camPosition.x = model->mapWidth * model->tileSize - windowWidth / 2;

	if (camPosition.y < windowHeight / 2)
		camPosition.y = windowHeight / 2;
	else if (camPosition.y > model->mapHeight * model->tileSize - windowHeight / 2)
		camPosition.y = model->mapHeight * model->tileSize - windowHeight / 2;

	camera.setCenter(camPosition);
	window.clear();
	window.setView(camera);

	for (std::vector<Tile>::iterator i = model->tileMap.begin(); i != model->tileMap.end(); i++) {
		window.draw(i->sprite);
	}

	model->player.sprite.setPosition(model->player.position);
	window.draw(model->player.sprite);

	window.display();
}