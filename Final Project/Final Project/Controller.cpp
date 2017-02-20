#include "Controller.h"



Controller::Controller(Model* newModel, Render* newView){
	model = newModel;
	view = newView;
}


Controller::~Controller(){ }

void Controller::inputs() {
	sf::Event event;

	while (view->window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			view->window.close();
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		model->player.velocity.y = -100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		model->player.velocity.y = 100;
	}
	else model->player.velocity.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		model->player.velocity.x = -100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		model->player.velocity.x = 100;
	}
	else model->player.velocity.x = 0;
}