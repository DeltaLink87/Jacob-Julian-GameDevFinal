#include "Render.h"
#include <sstream>


Render::Render(Model* newModel){
	model = newModel;

	windowWidth = 800;
	windowHeight = 600;

	window.create(sf::VideoMode(windowWidth, windowHeight), "LIVE DEMO");

	window.setFramerateLimit(60);

	camera.setSize(sf::Vector2f(windowWidth, windowHeight));

	//menuCamera.setSize(sf::Vector2f(410, 310));
	//menuCamera.setCenter(-1202.5, 155.0);

	font.loadFromFile("Assets/times.ttf");
	
	textBrush.setFont(font);
	textBrush.setCharacterSize(20);
	//textBrush.setFillColor(sf::Color::White);
	textBrush.setStyle(sf::Text::Regular);
	textBrush.setFillColor(sf::Color::Black);

	modelTexture.create(windowWidth, windowHeight);
	invMenuTexture.create(windowWidth, windowHeight);
	craftMenuTexture.create(windowWidth, windowHeight);

	/*for (std::map<std::string, Item*>::iterator i = model->itemManager->getAllItems().begin(); i != model->itemManager->getAllItems().end(); i++) {
		i->second->smallIconTexture = manager.loadTexture("Items/" + i->first + "Icon");
		i->second->smallIcon.setTexture(i->second->smallIconTexture);
		i->second->smallIcon.setScale(sf::Vector2f(75.0 / i->second->smallIcon.getTexture()->getSize().x, 75.0 / i->second->smallIcon.getTexture()->getSize().y));

		i->second->menuIconTexture = manager.loadTexture("Items/" + i->first + "Menu");
		i->second->menuIcon.setTexture(i->second->menuIconTexture);
		i->second->menuIcon.setScale(sf::Vector2f(.5, .5));

		i->second->menuDescriptionTexture = manager.loadTexture("Items/" + i->first + "Description");
		i->second->menuDescription.setTexture(i->second->menuDescriptionTexture);
	}*/

	initializeRenderable(model->player);
	for (std::vector<Enemy*>::iterator e = model->enemies.begin(); e != model->enemies.end(); e++) {
		initializeRenderable(*e);
	}
	for (int y = 0; y < model->mapHeight; y++) {
		for (int x = 0; x < model->mapWidth; x++) {
			initializeRenderable(model->tileMap[y][x]);
		}
	}
}

Render::~Render(){ }

void Render::initializeRenderable(Renderable* renderable) {
	//std::cout << renderable->textureName << std::endl;
	renderable->sprite.setTexture(manager.loadTexture(renderable->textureName));
	renderable->sprite.setScale(sf::Vector2f((float)renderable->spriteWidth / (float)renderable->sprite.getTextureRect().width, (float)renderable->spriteHeight / (float)renderable->sprite.getTextureRect().height));
	renderable->sprite.setPosition(renderable->getPosition());
	renderable->sprite.setRotation(renderable->rotation);
	renderable->spriteInitialized = true;
}

void Render::drawRenderable(sf::RenderTarget& target, Renderable* renderable) {
	renderable->sprite.setPosition(renderable->getPosition());
	target.draw(renderable->sprite);
}

void Render::render() {
	window.clear();

	renderModel();
	sf::Sprite modelSprite;
	modelSprite.setTexture(modelTexture.getTexture());
	window.draw(modelSprite);

	if (model->gameMode == 1) {
		renderCraftMenu();
		sf::Sprite craftMenuSprite;
		craftMenuSprite.setTexture(craftMenuTexture.getTexture());
		window.draw(craftMenuSprite);
	}
	else if (model->gameMode == 2) {
		renderInvMenu();
		sf::Sprite invMenuSprite;
		invMenuSprite.setTexture(invMenuTexture.getTexture());
		window.draw(invMenuSprite);
	}

	//window.draw(model->itemManager->getAllItems().at("Dagger")->menuIcon);

	window.display();
}

void Render::renderModel() {
	//finding camera position
	camPosition = model->player->getPosition();
	if (camPosition.x < windowWidth / 2)
		camPosition.x = windowWidth / 2;
	else if (camPosition.x > model->mapWidth * model->tileSize - windowWidth / 2)
		camPosition.x = model->mapWidth * model->tileSize - windowWidth / 2;

	if (camPosition.y < windowHeight / 2)
		camPosition.y = windowHeight / 2;
	else if (camPosition.y > model->mapHeight * model->tileSize - windowHeight / 2)
		camPosition.y = model->mapHeight * model->tileSize - windowHeight / 2;
	camera.setCenter(camPosition);

	modelTexture.clear();
	//updating the camera position
	modelTexture.setView(camera);

	//rendering tilemap
	for (int y = 0; y < model->mapHeight; y++) {
		for (int x = 0; x < model->mapWidth; x++) {
			drawRenderable(modelTexture, model->tileMap[y][x]);
		}
	}

	//rendering player
	drawRenderable(modelTexture, model->player);

	for (std::vector<Enemy*>::iterator i = model->enemies.begin(); i != model->enemies.end(); i++) {
		drawRenderable(modelTexture, *i);
	}

	//rendering attacks
	for (std::vector<Attack*>::iterator i = model->attacks.begin(); i != model->attacks.end(); i++) {
		if (!(*i)->spriteInitialized)
			initializeRenderable(*i);
		drawRenderable(modelTexture, *i);
	}

	//rendering the area of affect for sounds
	for (std::vector<Sound>::iterator i = model->sounds.begin(); i != model->sounds.end(); i++) {
		sf::CircleShape soundSphere = sf::CircleShape(i->getLoudness());
		soundSphere.setPosition(i->getPosition() - sf::Vector2f(soundSphere.getRadius(), soundSphere.getRadius()));
		soundSphere.setFillColor(sf::Color(0, 0, 255, 100));
		modelTexture.draw(soundSphere);
	}

	//rendering loot
	for (std::vector<Loot*>::iterator i = model->droppedLoot.begin(); i != model->droppedLoot.end(); i++) {
		if (!(*i)->spriteInitialized)
			initializeRenderable(*i);
		drawRenderable(modelTexture, *i);
	}

	modelTexture.display();
}

void Render::renderCraftMenu() {
	craftMenuTexture.clear(sf::Color::Transparent);

	border = sf::RectangleShape(sf::Vector2f(410, 310));
	border.setPosition(sf::Vector2f(195, 145));
	border.setFillColor(sf::Color::White);
	craftMenuTexture.draw(border);

	center = sf::RectangleShape(sf::Vector2f(400, 300));
	center.setPosition(sf::Vector2f(200, 150));
	center.setFillColor(sf::Color(100, 100, 100));
	craftMenuTexture.draw(center);

	divide = sf::RectangleShape(sf::Vector2f(5, 300));
	divide.setPosition(sf::Vector2f(330, 150));
	divide.setFillColor(sf::Color::White);
	craftMenuTexture.draw(divide);

	textBrush.setString("Items:");
	textBrush.setPosition(sf::Vector2f(205, 150));
	craftMenuTexture.draw(textBrush);

	int counter = 0;
	for (std::map<std::string, Item*>::iterator i = model->craftMenu->itemList.begin(); i != model->craftMenu->itemList.end(); i++) {
		//std::cout << model->itemManager->itemIndex.at(i+1) << std::endl;
		(*i).second->menuIcon.setPosition(sf::Vector2f(200, 175 + 75 * counter));
		craftMenuTexture.draw((*i).second->menuIcon);

		if (!model->craftMenu->canMake[counter]) {
			sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(130, 70));
			rect.setPosition(sf::Vector2f(200, 175 + 75 * counter));
			rect.setFillColor(sf::Color(0, 0, 0, 100));
			craftMenuTexture.draw(rect);
		}
		//textBrush.setPosition(sf::Vector2f(-1395, 30 * (i + 1)));
		//window.draw(textBrush);
		counter++;
	}
	model->craftMenu->selectedBox.setPosition(200, 175 + 75 * model->craftMenu->curSelected);
	craftMenuTexture.draw(model->craftMenu->selectedBox);

	model->craftMenu->itemList.at(model->craftMenu->itemNameList.at(model->craftMenu->curSelected))->menuDescription.setPosition(sf::Vector2f(335, 150));
	craftMenuTexture.draw(model->craftMenu->itemList.at(model->craftMenu->itemNameList.at(model->craftMenu->curSelected))->menuDescription);

	craftMenuTexture.display();
}

void Render::renderInvMenu() {
	invMenuTexture.clear(sf::Color::Transparent);

	border = sf::RectangleShape(sf::Vector2f(410, 310));
	border.setPosition(sf::Vector2f(195, 145));
	border.setFillColor(sf::Color::Black);
	invMenuTexture.draw(border);

	center = sf::RectangleShape(sf::Vector2f(400, 300));
	center.setPosition(sf::Vector2f(200, 150));
	center.setFillColor(sf::Color::White);
	invMenuTexture.draw(center);

	model->invMenu->iMenuSprite.setPosition(200, 150);
	invMenuTexture.draw(model->invMenu->iMenuSprite);

	int counter = 0;
	Inventory* inv = model->player->getInventory();
	for (int y = 0; y < inv->getHeight(); y++)
		for (int x = 0; x < inv->getWidth(); x++) {
			Item* curItem = inv->getCurSeletected(x, y);
			if (curItem != NULL) {
				curItem->smallIcon.setPosition(
					200 + model->invMenu->iSlotStart.x + x * (model->invMenu->iSlotOff.x + model->invMenu->iSlotDim.x),
					150 + model->invMenu->iSlotStart.y + y * (model->invMenu->iSlotOff.y + model->invMenu->iSlotDim.y));
				curItem->smallIcon.setScale(1.0 / (curItem->smallIcon.getLocalBounds().width / model->invMenu->iSlotDim.x),
					1.0 / (curItem->smallIcon.getLocalBounds().height / model->invMenu->iSlotDim.y));
				invMenuTexture.draw(curItem->smallIcon);
				

				std::stringstream ss;
				ss << curItem->quantity;
				textBrush.setString(ss.str());
				textBrush.setPosition(sf::Vector2f(
					200 + model->invMenu->iSlotStart.x + (x + 0.6) * (model->invMenu->iSlotOff.x + model->invMenu->iSlotDim.x),
					150 + model->invMenu->iSlotStart.y + (y + 0.5) * (model->invMenu->iSlotOff.y + model->invMenu->iSlotDim.y)));
				invMenuTexture.draw(textBrush);
			}
		}

	model->invMenu->selectedBox.setPosition(
		200 + model->invMenu->iSlotStart.x + ((model->invMenu->iSlotDim.x + model->invMenu->iSlotOff.x) * model->invMenu->curX),
		150 + (model->invMenu->iSlotStart.y + ((model->invMenu->iSlotDim.y + model->invMenu->iSlotOff.y) * model->invMenu->curY)));
	model->invMenu->selectedBox.setOutlineColor(sf::Color::Green);
	invMenuTexture.draw(model->invMenu->selectedBox);

	invMenuTexture.display();
}
