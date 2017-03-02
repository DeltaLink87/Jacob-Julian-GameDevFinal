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
			/*
					case sf::Event::MouseWheelScrolled:
						if (event.mouseWheel.delta != 0) {
							float scroll = (float)event.mouseWheelScroll.delta;
						}
						break;
						*/
		case sf::Event::MouseWheelScrolled:
			if (event.mouseWheelScroll.delta != 0) {
				this->view->camera.zoom(1.0 - (((float)event.mouseWheelScroll.delta) * 0.1));
			}
			break;
		case sf::Event::KeyPressed:
			//Pressing Esc will close the window
			if (event.key.code == sf::Keyboard::Escape)
				this->view->window.close();
			break;
		}
		
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		model->player.velocity.y = -100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		model->player.velocity.y = 100;
	}
	else model->player.velocity.y = 0;*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		model->player.velocity.x = -100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		model->player.velocity.x = 100;
	}
	else model->player.velocity.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!prevSpacePressed) {
			model->player.jump = true;
			prevSpacePressed = true;
		}
		else model->player.jump = false;
	}
	else {
		prevSpacePressed = false;
		model->player.jump = false;
	}
}