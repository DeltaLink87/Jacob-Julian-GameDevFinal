#include "Render.h"


Render::Render(Model* newModel){
	model = newModel;

	windowWidth = 800;
	windowHeight = 600;

	window.create(sf::VideoMode(windowWidth, windowHeight), "LIVE DEMO");

	window.setFramerateLimit(60);

	camera.setSize(sf::Vector2f(windowWidth, windowHeight));

	menuCamera.setSize(sf::Vector2f(410, 310));
	menuCamera.setCenter(-1202.5, 155.0);

	font.loadFromFile("Assets/times.ttf");
	
	textBrush.setFont(font);
	textBrush.setCharacterSize(20);
	textBrush.setFillColor(sf::Color::White);
	textBrush.setStyle(sf::Text::Regular);



}

Render::~Render(){ }

void Render::render() {
	//finding camera position
	camPosition = model->player.getPosition();
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
	for (int y = 0; y < model->mapHeight; y++){
		for (int x = 0; x < model->mapWidth; x++) {
			window.draw(model->tileMap[y][x]->sprite);
		}
	}

	//rendering player
	model->player.sprite.setPosition(model->player.getPosition());
	window.draw(model->player.sprite);

	for (std::vector<Enemy*>::iterator i = model->enemies.begin(); i != model->enemies.end(); i++) {
		(*i)->sprite.setPosition((*i)->getPosition());
		window.draw((*i)->sprite);
	}

	//rendering attacks
	for (std::vector<Attack*>::iterator i = model->attacks.begin(); i != model->attacks.end(); i++) {
		(*i)->sprite.setPosition((*i)->getPosition());
		window.draw((*i)->sprite);
	}

	//rendering the area of affect for sounds
	for (std::vector<Sound>::iterator i = model->sounds.begin(); i != model->sounds.end(); i++) {
		sf::CircleShape soundSphere = sf::CircleShape(i->getLoudness());
		soundSphere.setPosition(i->getPosition() - sf::Vector2f(soundSphere.getRadius(), soundSphere.getRadius()));
		soundSphere.setFillColor(sf::Color(0,0,255,100));
		window.draw(soundSphere);
	}

	for (std::vector<Loot*>::iterator i = model->droppedLoot.begin(); i != model->droppedLoot.end(); i++)
		window.draw((*i)->sprite);
  
	if (model->gameMode == 1) {
		camera.setCenter(menuCamera.getCenter());
		window.setView(camera);
		renderMenu();
	}
  
	window.display();
}

void Render::renderMenu() {

	sf::RectangleShape border = sf::RectangleShape(sf::Vector2f(410, 310));
	border.setPosition(sf::Vector2f(-1405, 0));
	border.setFillColor(sf::Color::White);

	sf::RectangleShape center = sf::RectangleShape(sf::Vector2f(400, 300));
	center.setPosition(sf::Vector2f(-1400, 5));
	center.setFillColor(sf::Color(100, 100, 100));

	sf::RectangleShape divide = sf::RectangleShape(sf::Vector2f(5, 300));
	divide.setPosition(sf::Vector2f(-1270, 5));
	divide.setFillColor(sf::Color::White);

	window.draw(border);
	window.draw(center);
	window.draw(divide);

	textBrush.setString("Items:");
	textBrush.setPosition(sf::Vector2f(-1395, 5));
	window.draw(textBrush);
	
	int counter = 0;
	for (std::map<std::string, Item*>::iterator i = model->craftMenu->itemList.begin(); i != model->craftMenu->itemList.end(); i++) {
		//std::cout << model->itemManager->itemIndex.at(i+1) << std::endl;
		(*i).second->menuIcon.setPosition(sf::Vector2f(-1400, 30 + 75 * counter));
		window.draw((*i).second->menuIcon);

		if (!model->craftMenu->canMake[counter]) {
			sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(130, 70));
			rect.setPosition(sf::Vector2f(-1400, 30 + 75 * counter));
			rect.setFillColor(sf::Color(0, 0, 0, 100));
			window.draw(rect);
		}
		//textBrush.setPosition(sf::Vector2f(-1395, 30 * (i + 1)));
		//window.draw(textBrush);
		counter++;
	}
	model->craftMenu->selectedBox.setPosition(-1400, 30 + 75 * model->craftMenu->curSelected);
	window.draw(model->craftMenu->selectedBox);

	model->craftMenu->itemList.at(model->craftMenu->itemNameList.at(model->craftMenu->curSelected))->menuDescription.setPosition(sf::Vector2f(-1265, 5));
	window.draw(model->craftMenu->itemList.at(model->craftMenu->itemNameList.at(model->craftMenu->curSelected))->menuDescription);
}