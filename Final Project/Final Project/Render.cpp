#include "Render.h"


Render::Render(Model* newModel){
	model = newModel;

	windowWidth = 800;
	windowHeight = 600;

	window.create(sf::VideoMode(windowWidth, windowHeight), "LIVE DEMO");

	window.setFramerateLimit(60);

	camera.setSize(sf::Vector2f(windowWidth, windowHeight));
}

Render::~Render(){ }

void Render::render() {
	//finding camera position
	sf::Vector2f camPosition = model->player.position;
	if (camPosition.x < windowWidth / 2)
		camPosition.x = windowWidth / 2;
	else if (camPosition.x > model->mapWidth * model->tileSize - windowWidth / 2)
		camPosition.x = model->mapWidth * model->tileSize - windowWidth / 2;

	if (camPosition.y < windowHeight / 2)
		camPosition.y = windowHeight / 2;
	else if (camPosition.y > model->mapHeight * model->tileSize - windowHeight / 2)
		camPosition.y = model->mapHeight * model->tileSize - windowHeight / 2;

	//updating the camera position
	camera.setCenter(camPosition);
	window.clear();
	window.setView(camera);

	//rendering tilemap
	for (std::vector<Tile>::iterator i = model->tileMap.begin(); i != model->tileMap.end(); i++) {
		window.draw(i->sprite);
	}

	//rendering player
	model->player.sprite.setPosition(model->player.position);
	model->test->sprite.setPosition(model->test->position);
	window.draw(model->player.sprite);
	window.draw(model->test->sprite);

	//rendering attacks
	for (std::vector<Attack*>::iterator i = model->attacks.begin(); i != model->attacks.end(); i++) {
		(*i)->sprite.setPosition((*i)->position);
		window.draw((*i)->sprite);
	}

	//rendering the area of affect for sounds
	for (std::vector<Sound>::iterator i = model->sounds.begin(); i != model->sounds.end(); i++) {
		sf::CircleShape soundSphere = sf::CircleShape(i->loudness);
		soundSphere.setPosition(i->position - sf::Vector2f(soundSphere.getRadius(), soundSphere.getRadius()));
		soundSphere.setFillColor(sf::Color(0,0,255,100));
		window.draw(soundSphere);
	}

	window.display();
}