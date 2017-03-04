#include "Controller.h"
#include <iostream>


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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		model->player.up = true;
	}
	else model->player.up = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		model->player.down = true;
	}
	else model->player.down = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		model->player.left = true;
	}
	else model->player.left = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		model->player.right = true;
	}
	else model->player.right = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		model->player.moveSlow = true;
	}
	else model->player.moveSlow = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		model->player.moveFast = true;
	}
	else model->player.moveFast = false;

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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		model->player.isAttacking(true);
	}
	else model->player.isAttacking(false);

	model->player.looking = sf::Vector2f((sf::Vector2f)sf::Mouse::getPosition(view->window) + view->camPosition - (sf::Vector2f)view->window.getSize() * 0.5f);
	//std::cout << model->player.looking.x << "," << model->player.looking.y << std::endl;
}