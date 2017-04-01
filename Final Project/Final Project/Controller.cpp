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
	/*inputTo->up = false;
	inputTo->down = false;
	inputTo->left = false;
	inputTo->right = false;
	inputTo->moveSlow = false;
	inputTo->moveFast = false;
	inputTo->jump = false;
	inputTo->select = false;
	inputTo->pressAttack = false;*/
	inputTo->craftingMenu = false;
	inputTo->inventoryMenu = false;
	inputTo->toMainMenu = false;
	/*inputTo->mouse2 = false;
	inputTo->scrollRight = false;
	inputTo->scrollLeft = false;
	inputTo->mouseLessAttack = false;*/

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

		//checking for pressed mouse buttons
		case sf::Event::MouseButtonPressed:
			if (event.key.code == sf::Mouse::Left)
				inputTo->pressAttack = true;

			if (event.key.code == sf::Mouse::Right)
				inputTo->mouse2 = true;
			break;

		//checking for release mouse buttons
		case sf::Event::MouseButtonReleased:
			if (event.key.code == sf::Mouse::Left)
				inputTo->pressAttack = false;

			if (event.key.code == sf::Mouse::Right)
				inputTo->mouse2 = false;
			break;

		//checking for pressed keyboard buttons
		case sf::Event::KeyPressed:
			//Pressing Esc will close the window
			if (event.key.code == sf::Keyboard::Escape)
				this->view->window.close();

			if (event.key.code ==  sf::Keyboard::W)
				inputTo->up = true;

			if (event.key.code ==  sf::Keyboard::S)
				inputTo->down = true;

			if (event.key.code == sf::Keyboard::A)
				inputTo->left = true;

			if (event.key.code == sf::Keyboard::D)
				inputTo->right = true;

			if (event.key.code == sf::Keyboard::LShift)
				inputTo->moveSlow = true;

			if (event.key.code == sf::Keyboard::LControl)
				inputTo->moveFast = true;

			if (event.key.code == sf::Keyboard::Space) {
				//checking if space was held
				if (!prevSpacePressed) 
					inputTo->jump = true;
				else inputTo->jump = false;
				prevSpacePressed = true;
				inputTo->select = true;
			}

			if (event.key.code == sf::Keyboard::E) {
				//checking if E was held
				if (!prevCMenuPressed)
					inputTo->craftingMenu = true;
				else inputTo->craftingMenu = false;
				prevCMenuPressed = true;
			}

			if (event.key.code == sf::Keyboard::I) {
				//checking if I was held
				if (!prevIMenuPressed)
					inputTo->inventoryMenu = true;
				else inputTo->inventoryMenu = false;
				prevIMenuPressed = true;
			}

			if (event.key.code == sf::Keyboard::M) {
				//checking if M was held
				if (!prevchangeLevelPressed)
					inputTo->toMainMenu = true;
				else inputTo->toMainMenu = false;
				prevchangeLevelPressed = true;
			}

			if (event.key.code == sf::Keyboard::L)
				inputTo->scrollRight = true;

			if (event.key.code == sf::Keyboard::K)
				inputTo->scrollLeft = true;

			if (event.key.code == sf::Keyboard::J)
				inputTo->mouseLessAttack = true;

			if (event.key.code == sf::Keyboard::SemiColon)
				inputTo->mouse2 = true;
			break;

		//checking for released buttons
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::W)
				inputTo->up = false;

			if (event.key.code == sf::Keyboard::S)
				inputTo->down = false;

			if (event.key.code == sf::Keyboard::A)
				inputTo->left = false;

			if (event.key.code == sf::Keyboard::D)
				inputTo->right = false;

			if (event.key.code == sf::Keyboard::LShift)
				inputTo->moveSlow = false;

			if (event.key.code == sf::Keyboard::LControl)
				inputTo->moveFast = false;

			if (event.key.code == sf::Keyboard::Space) {
				prevSpacePressed = false;
				inputTo->jump = false;
				inputTo->select = false;
			}

			if (event.key.code == sf::Keyboard::E) {
				prevCMenuPressed = false;
				inputTo->craftingMenu = false;
			}

			if (event.key.code == sf::Keyboard::I) {
				prevIMenuPressed = false;
				inputTo->inventoryMenu = false;
			}

			if (event.key.code == sf::Keyboard::M) {
				prevchangeLevelPressed = false;
				inputTo->toMainMenu = false;
			}

			if (event.key.code == sf::Keyboard::L)
				inputTo->scrollRight = false;

			if (event.key.code == sf::Keyboard::K)
				inputTo->scrollLeft = false;

			if (event.key.code == sf::Keyboard::J)
				inputTo->mouseLessAttack = false;

			if (event.key.code == sf::Keyboard::SemiColon)
				inputTo->mouse2 = false;
			break;
		}
	}

	//getting mouse position relative to the top left corner of the map
	inputTo->looking = sf::Vector2f((sf::Vector2f)sf::Mouse::getPosition(view->window) + view->camPosition - (sf::Vector2f)view->window.getSize() * 0.5f);
	//std::cout << model->player.looking.x << "," << model->player.looking.y << std::endl;
}