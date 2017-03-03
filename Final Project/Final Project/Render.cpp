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
	sf::Vector2f camPosition = model->player.getPosition();
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
  
	camera.setCenter(menuCamera.getCenter());
	window.setView(camera);
	renderMenu();
  
	window.display();
}

void Render::renderMenu() {

	sf::RectangleShape border = sf::RectangleShape(sf::Vector2f(410, 310));
	border.setPosition(sf::Vector2f(-1405, 0));
	border.setFillColor(sf::Color::White);

	sf::RectangleShape center = sf::RectangleShape(sf::Vector2f(400, 300));
	center.setPosition(sf::Vector2f(-1400, 5));
	center.setFillColor(sf::Color::Black);

	sf::RectangleShape divide = sf::RectangleShape(sf::Vector2f(5, 300));
	divide.setPosition(sf::Vector2f(-1270, 5));
	divide.setFillColor(sf::Color::White);

	window.draw(border);
	window.draw(center);
	window.draw(divide);

	textBrush.setString("Items:");
	textBrush.setPosition(sf::Vector2f(-1395, 5));
	window.draw(textBrush);
	
	for (int i = 0; i < model->itemManager->itemIndex.size(); i++) {
		//std::cout << model->itemManager->itemIndex.at(i+1) << std::endl;
		model->itemManager->items.at(model->itemManager->itemIndex.at(i + 1))->menuIcon.setPosition(sf::Vector2f(-1400, 20 + 75 * i));
		window.draw(model->itemManager->items.at(model->itemManager->itemIndex.at(i+1))->menuIcon);
		//textBrush.setPosition(sf::Vector2f(-1395, 30 * (i + 1)));
		//window.draw(textBrush);
	}
	


}