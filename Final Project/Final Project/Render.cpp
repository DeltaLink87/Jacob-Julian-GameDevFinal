#include "Render.h"


Render::Render(Model* newModel){
	model = newModel;

	windowWidth = 800;
	windowHeight = 600;

	window.create(sf::VideoMode(windowWidth, windowHeight), "LIVE DEMO");

	window.setFramerateLimit(30);
}

Render::~Render(){ }

void Render::render() {
	window.clear();

	model->player.sprite.setPosition(model->player.position);
	window.draw(model->player.sprite);

	window.display();
}