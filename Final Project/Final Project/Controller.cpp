#include "Controller.h"
#include <iostream>


Controller::Controller(Model* newModel, Render* newView){
	model = newModel;
	view = newView;

	inputTo = model->player;
	//inputTo = model->craftMenu;
}


Controller::~Controller(){ }

void Controller::inputs() {
	if (model->gameMode == 0)
		inputTo = model->player;
	else if (model->gameMode == 1)
		inputTo = model->craftMenu;
	else if (model->gameMode == 2)
		inputTo = model->invMenu;
	else if (model->gameMode == 7)
		inputTo = &(model->mainMenu);

	sf::Event event;

	inputTo->scroll = 0;

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
				//this->view->camera.zoom(1.0 - (((float)event.mouseWheelScroll.delta) * 0.1));
				inputTo->scroll = event.mouseWheelScroll.delta;
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
		inputTo->up = true;
	}
	else inputTo->up = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		inputTo->down = true;
	}
	else inputTo->down = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		inputTo->left = true;
	}
	else inputTo->left = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		inputTo->right = true;
	}
	else inputTo->right = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		inputTo->moveSlow = true;
	}
	else inputTo->moveSlow = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		inputTo->moveFast = true;
	}
	else inputTo->moveFast = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!prevSpacePressed) {
			inputTo->jump = true;
			prevSpacePressed = true;
		}
		else inputTo->jump = false;
		inputTo->select = true;
	}
	else {
		prevSpacePressed = false;
		inputTo->jump = false;
		inputTo->select = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		inputTo->pressAttack = true;
	}
	else inputTo->pressAttack = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		inputTo->mouse2 = true;
	}
	else inputTo->mouse2 = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		if (!prevCMenuPressed) {
			inputTo->craftingMenu = true;
			prevCMenuPressed = true;
		}
		else
			inputTo->craftingMenu = false;
	}
	else {
		inputTo->craftingMenu = false;
		prevCMenuPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		if (!prevIMenuPressed) {
			inputTo->inventoryMenu = true;
			prevIMenuPressed = true;
		}
		else
			inputTo->inventoryMenu = false;
	}
	else {
		inputTo->inventoryMenu = false;
		prevIMenuPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		if (!prevchangeLevelPressed) {
			inputTo->toMainMenu = true;
			prevchangeLevelPressed = true;
		}
		else inputTo->toMainMenu = false;
	}
	else {
		inputTo->toMainMenu = false;
		prevchangeLevelPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		inputTo->scrollRight = true;
	}
	else inputTo->scrollRight = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		inputTo->scrollLeft = true;
	}
	else inputTo->scrollLeft = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		inputTo->mouseLessAttack = true;
	}
	else inputTo->mouseLessAttack = false;

	inputTo->looking = sf::Vector2f((sf::Vector2f)sf::Mouse::getPosition(view->window) + view->camPosition - (sf::Vector2f)view->window.getSize() * 0.5f);
	//std::cout << model->player.looking.x << "," << model->player.looking.y << std::endl;
}