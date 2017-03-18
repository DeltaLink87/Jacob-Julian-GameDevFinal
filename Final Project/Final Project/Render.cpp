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
	UITexture.create(windowWidth, windowHeight);
	mainMenuTexture.create(windowWidth, windowHeight);

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

	/*initializeRenderable(model->player);
	for (std::vector<Enemy*>::iterator e = model->enemies.begin(); e != model->enemies.end(); e++) {
		initializeRenderable(*e);
	}
	for (int y = 0; y < model->mapHeight; y++) {
		for (int x = 0; x < model->mapWidth; x++) {
			initializeRenderable(model->tileMap[y][x]);
		}
	}*/

	model->mainMenu.titleCardSprite.setTexture(manager.loadTexture("MainMenu/TitleCard"));
	model->mainMenu.titleCardSprite.setPosition(windowWidth / 2 - 100, windowHeight / 2 - 200);
	model->mainMenu.optionSprite[0].setTexture(manager.loadTexture("MainMenu/StartButton"));
	model->mainMenu.optionSprite[0].setPosition(windowWidth / 2 - 100, windowHeight / 2);
	model->mainMenu.optionSprite[1].setTexture(manager.loadTexture("MainMenu/StageButton"));
	model->mainMenu.optionSprite[1].setPosition(windowWidth / 2 - 100, windowHeight / 2 + 100);


	/*
	playerSpriteSheet.loadFromFile("Assets/Textures/Actors/playerSheet.png");

	this->playerSprites.setPrimitiveType(sf::Quads);
	this->playerSprites.resize(80);

	for (int i = 0; i < 3; i++) {
		
		playerSprites[i * 4 + 0].texCoords = sf::Vector2f(i * 16, 0);

		playerSprites[i * 4 + 1].texCoords = sf::Vector2f(i * 16  + 16, 0);

		playerSprites[i * 4 + 2].texCoords = sf::Vector2f(i * 16, 16);

		playerSprites[i * 4 + 3].texCoords = sf::Vector2f(i * 16, 16);

		playerSprites[50]

	}
	*/


}

Render::~Render(){ }

void Render::initializeRenderable(Renderable* renderable) {
	//std::cout << renderable->textureName << std::endl;
	renderable->sprite.setTexture(manager.loadTexture(renderable->textureName));
	renderable->sprite.setScale(sf::Vector2f((float)renderable->spriteWidth / (float)renderable->sprite.getTextureRect().width, (float)renderable->spriteHeight / (float)renderable->sprite.getTextureRect().height));
	renderable->sprite.setPosition(renderable->getPosition());
	renderable->sprite.setRotation(renderable->spriteRotation);
	renderable->spriteInitialized = true;
}

void Render::drawRenderable(sf::RenderTarget& target, Renderable* renderable) {
	if (!renderable->spritePositionSet)
		renderable->sprite.setPosition(renderable->getPosition());
	target.draw(renderable->sprite);
}

void Render::render() {
	window.clear();

	renderModel();
	sf::Sprite modelSprite;
	modelSprite.setTexture(modelTexture.getTexture());
	window.draw(modelSprite);

	if (model->gameMode != 7)
		renderUI();

	if (model->gameMode == 3) {
		renderWin();
	}

	if (model->gameMode != 7) {
		sf::Sprite UISprite;
		UISprite.setTexture(UITexture.getTexture());
		window.draw(UISprite);
	}

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

	if (model->gameMode == 4) {
		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(windowWidth, windowHeight));
		rect.setFillColor(sf::Color(0, 0, 0, 255 * screenAlpha));
		screenAlpha += 0.1;
		if (screenAlpha >= 1) {
			screenAlpha = 1;
			model->renderDone = true;
		}
		window.draw(rect);
	}
	else if (model->gameMode == 5) {
		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(windowWidth, windowHeight));
		rect.setFillColor(sf::Color::Black);
		window.draw(rect);
	}
	else if (model->gameMode == 6) {
		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(windowWidth, windowHeight));
		rect.setFillColor(sf::Color(0, 0, 0, 255 * screenAlpha));
		screenAlpha -= 0.1;
		if (screenAlpha <= 0) {
			screenAlpha = 0;
			model->renderDone = true;
		}
		window.draw(rect);
	}

	if (model->gameMode == 7) {
		renderMainMenu();
		sf::Sprite mainMenuSprite;
		mainMenuSprite.setTexture(mainMenuTexture.getTexture());
		window.draw(mainMenuSprite);
	}

	window.display();
}

void Render::renderModel() {
	//finding camera position
	camPosition = model->player->getPosition();
	if (model->mapWidth * model->tileSize <= windowWidth)
		camPosition.x = model->mapWidth * model->tileSize / 2;
	else if (camPosition.x < windowWidth / 2)
		camPosition.x = windowWidth / 2;
	else if (camPosition.x > model->mapWidth * model->tileSize - windowWidth / 2)
		camPosition.x = model->mapWidth * model->tileSize - windowWidth / 2;

	if (model->mapHeight * model->tileSize <= windowHeight)
		camPosition.y = model->mapHeight * model->tileSize / 2;
	else if (camPosition.y < windowHeight / 2)
		camPosition.y = windowHeight / 2;
	else if (camPosition.y > model->mapHeight * model->tileSize - windowHeight / 2)
		camPosition.y = model->mapHeight * model->tileSize - windowHeight / 2;
	camera.setCenter(camPosition);

	modelTexture.clear(sf::Color::Transparent);
	//updating the camera position
	modelTexture.setView(camera);

	//rendering tilemap
	for (int y = 0; y < model->mapHeight; y++) {
		for (int x = 0; x < model->mapWidth; x++) {
			if (!model->tileMap[y][x]->spriteInitialized)
				initializeRenderable(model->tileMap[y][x]);
			drawRenderable(modelTexture, model->tileMap[y][x]);
		}
	}

	//rendering player
	if (!model->player->spriteInitialized)
		initializeRenderable(model->player);
	drawRenderable(modelTexture, model->player);

	for (std::vector<Enemy*>::iterator i = model->enemies.begin(); i != model->enemies.end(); i++) {
		if (!(*i)->isRemoved()) {
			if (!(*i)->spriteInitialized)
				initializeRenderable(*i);
			drawRenderable(modelTexture, *i);

			sf::Vertex* path = new sf::Vertex[(*i)->path.size()];
			for (int l = 0; l < (*i)->path.size(); l++) {
				path[l].position = (*i)->path.at(l);
				path[l].color = sf::Color::Red;
			}
			modelTexture.draw(path, (*i)->path.size(), sf::LineStrip);

			sf::Vertex looking[2];
			looking[0].position = (*i)->getPosition() + (*i)->getHitBox().getSize() * 0.5f;
			looking[1].position = sf::Vector2f(looking[0].position.x + 32 * cos((*i)->dirLooking), looking[0].position.y + 32 * sin((*i)->dirLooking));
			modelTexture.draw(looking, 2, sf::Lines);
		}
	}

	//rendering attacks
	for (std::vector<Attack*>::iterator i = model->attacks.begin(); i != model->attacks.end(); i++) {
		if (!(*i)->spriteInitialized)
			initializeRenderable(*i);
		modelTexture.draw((*i)->getHitBox());
		drawRenderable(modelTexture, *i);
		
	}

	//rendering the area of affect for sounds
	for (std::vector<Sound>::iterator i = model->sounds.begin(); i != model->sounds.end(); i++) {
		sf::CircleShape soundSphere = sf::CircleShape(i->getLoudness() * i->getPercentTimeLeft());
		soundSphere.setPosition(i->getPosition() - sf::Vector2f(soundSphere.getRadius(), soundSphere.getRadius()));
		soundSphere.setFillColor(sf::Color::Transparent);
		soundSphere.setOutlineThickness(2);
		soundSphere.setOutlineColor(sf::Color(255, 255, 255, 255 * (1 - i->getPercentTimeLeft())));
		modelTexture.draw(soundSphere);
	}
	
	//rendering loot
	for (std::vector<Loot*>::iterator i = model->droppedLoot.begin(); i != model->droppedLoot.end(); i++) {
		if (!(*i)->spriteInitialized)
			initializeRenderable(*i);
		drawRenderable(modelTexture, *i);
	}

	for (std::vector<Objective*>::iterator i = model->levelObjectives.begin(); i != model->levelObjectives.end(); i++) {
		if (!(*i)->isComplete()) {
			if (!(*i)->initialized) {
				(*i)->objFlagSprite.setTexture(manager.loadTexture((*i)->flagTextureName));
				(*i)->objFlagSprite.setScale(sf::Vector2f((float)(*i)->flagWidth / (float)(*i)->objFlagSprite.getTextureRect().width, (float)(*i)->flagHeight / (float)(*i)->objFlagSprite.getTextureRect().height));
				(*i)->initialized = true;
			}
			(*i)->objFlagSprite.setPosition((*i)->getPosition() + (*i)->flagPosDif);
			modelTexture.draw((*i)->objFlagSprite);
		}
	}

	modelTexture.display();
	UITexture.display();
}

void Render::renderUI() {
	UITexture.clear(sf::Color::Transparent);

	sf::Sprite quickBar;
	quickBar.setTexture(manager.loadTexture("UI/QuickBar"));
	quickBar.setScale(160.0 / (float)quickBar.getTextureRect().width, 32.0 / (float)quickBar.getTextureRect().height);
	UITexture.draw(quickBar);

	sf::Sprite healthBox;
	healthBox.setTexture(manager.loadTexture("UI/HealthBox"));
	healthBox.setScale(64.0 / (float)healthBox.getTextureRect().width, 32.0 / (float)healthBox.getTextureRect().height);
	healthBox.setPosition(windowWidth - 64, 0);
	UITexture.draw(healthBox);

	for (int i = 0; i < model->player->getInventory()->getHeight(); i++) {
		Item* item = model->player->getInventory()->getCurSeletected(i);
		if (item != NULL) {
			sf::Sprite sprite;
			sprite.setTexture(item->smallIconTexture);
			sprite.setScale(32.0 / (float)sprite.getTextureRect().width, 32.0 / (float)sprite.getTextureRect().height);
			sprite.setPosition(i * 32, 0);
			UITexture.draw(sprite);

			std::stringstream ss;
			ss << item->quantity;
			textBrush.setString(ss.str());
			textBrush.setPosition(i * 32 + 20, 9);
			UITexture.draw(textBrush);
		}
	}

	sf::RectangleShape select = sf::RectangleShape(sf::Vector2f(32, 32));
	select.setPosition(model->player->getCurSelected() * 32, 0);
	select.setFillColor(sf::Color::Transparent);
	select.setOutlineColor(sf::Color::White);
	select.setOutlineThickness(3);
	UITexture.draw(select);

	std::stringstream ss;
	ss << model->player->getHealth() << "/" << model->player->getMaxHealth();
	textBrush.setString(ss.str());
	textBrush.setPosition(windowWidth - 60, 2);
	UITexture.draw(textBrush);
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

	int counter = 0, firstRender, lastRender;
	if (model->craftMenu->curSelected < 2) {
		firstRender = 0;
		lastRender = 3;
	}
	else if (model->craftMenu->curSelected >= model->craftMenu->totalItems - 2) {
		firstRender = model->craftMenu->totalItems - 4;
		lastRender = model->craftMenu->totalItems - 1;
	}
	else {
		firstRender = model->craftMenu->curSelected - 2;
		lastRender = model->craftMenu->curSelected + 1;
	}
	for (std::map<std::string, Item*>::iterator i = model->craftMenu->itemList.begin(); i != model->craftMenu->itemList.end(); i++) {
		if (counter >= firstRender && counter <= lastRender) {
			//std::cout << model->itemManager->itemIndex.at(i+1) << std::endl;
			i->second->menuIcon.setPosition(sf::Vector2f(200, 175 + 75 * (counter - firstRender)));
			craftMenuTexture.draw(i->second->menuIcon);

			if (!model->craftMenu->canMake[counter]) {
				sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(130, 70));
				rect.setPosition(sf::Vector2f(200, 175 + 75 * (counter - firstRender)));
				rect.setFillColor(sf::Color(0, 0, 0, 100));
				craftMenuTexture.draw(rect);
			}
		}

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

	int top = 125;
	int left = 173;

	/*border = sf::RectangleShape(sf::Vector2f(410, 310));
	border.setPosition(sf::Vector2f(195, 145));
	border.setFillColor(sf::Color::Black);
	invMenuTexture.draw(border);

	center = sf::RectangleShape(sf::Vector2f(400, 300));
	center.setPosition(sf::Vector2f(200, 150));
	center.setFillColor(sf::Color::White);
	invMenuTexture.draw(center);*/

	model->invMenu->iMenuSprite.setPosition(left, top);
	invMenuTexture.draw(model->invMenu->iMenuSprite);

	int counter = 0;
	Inventory* inv = model->player->getInventory();
	for (int y = 0; y < inv->getHeight(); y++) {
		for (int x = 0; x < inv->getWidth(); x++) {
			Item* curItem = inv->getCurSeletected(x, y);
			if (curItem != NULL) {
				curItem->smallIcon.setPosition(
					left + model->invMenu->iSlotStart.x + x * (model->invMenu->iSlotOff.x + model->invMenu->iSlotDim.x),
					top + model->invMenu->iSlotStart.y + y * (model->invMenu->iSlotOff.y + model->invMenu->iSlotDim.y));
				curItem->smallIcon.setScale(1.0 / (curItem->smallIcon.getLocalBounds().width / model->invMenu->iSlotDim.x),
					1.0 / (curItem->smallIcon.getLocalBounds().height / model->invMenu->iSlotDim.y));
				invMenuTexture.draw(curItem->smallIcon);


				std::stringstream ss;
				ss << curItem->quantity;
				textBrush.setString(ss.str());
				textBrush.setPosition(sf::Vector2f(
					left + model->invMenu->iSlotStart.x + (x + 0.6) * (model->invMenu->iSlotOff.x + model->invMenu->iSlotDim.x),
					top + model->invMenu->iSlotStart.y + (y + 0.5) * (model->invMenu->iSlotOff.y + model->invMenu->iSlotDim.y)));
				invMenuTexture.draw(textBrush);
			}
		}
	}

	//std::cout << model->invMenu->getCurX() << "," << model->invMenu->getCurY() << "," << inv->getWidth() << "," << inv->getHeight() << std::endl;
	Item* item = inv->getCurSeletected(model->invMenu->getCurX(), model->invMenu->getCurY());
	if (item != NULL) {
		item->menuDescription.setPosition(left + 5, top + 5);
		item->menuDescription.setScale(226.0 / (float)item->menuDescription.getTextureRect().width, 237.0 / (float)item->menuDescription.getTextureRect().height);
		invMenuTexture.draw(item->menuDescription);
	}

	model->invMenu->selectedBox.setPosition(
		left + model->invMenu->iSlotStart.x + ((model->invMenu->iSlotDim.x + model->invMenu->iSlotOff.x) * model->invMenu->getCurX()),
		top + (model->invMenu->iSlotStart.y + ((model->invMenu->iSlotDim.y + model->invMenu->iSlotOff.y) * model->invMenu->getCurY())));
	model->invMenu->selectedBox.setOutlineColor(sf::Color::Green);
	invMenuTexture.draw(model->invMenu->selectedBox);

	invMenuTexture.display();
}

void Render::renderMainMenu() {
	mainMenuTexture.clear(sf::Color::Transparent);

	mainMenuTexture.draw(model->mainMenu.titleCardSprite);
	if (!model->mainMenu.stageSelect) {
		mainMenuTexture.draw(model->mainMenu.optionSprite[0]);
		mainMenuTexture.draw(model->mainMenu.optionSprite[1]);

		sf::RectangleShape select = sf::RectangleShape(sf::Vector2f(200, 100));
		select.setPosition(windowWidth / 2 - 100, windowHeight / 2 + 100 * model->mainMenu.getCurSelect());
		select.setFillColor(sf::Color::Transparent);
		select.setOutlineThickness(5);
		select.setOutlineColor(sf::Color::Black);
		mainMenuTexture.draw(select);
	}
	else {
		int first, last;
		if (model->mainMenu.totalStages < 3) {
			first = 0;
			last = model->mainMenu.totalStages;
		}
		else if (model->mainMenu.getCurSelect() > model->mainMenu.totalStages - 2) {
			first = model->mainMenu.totalStages - 3;
			last = model->mainMenu.totalStages;
		}
		else if (model->mainMenu.getCurSelect() < 2) {
			first = 0;
			last = 3;
		}
		else {
			first = model->mainMenu.getCurSelect() - 1;
			last = model->mainMenu.getCurSelect() + 2;
		}

		for (int i = first; i < last; i++) {
			sf::RectangleShape button = sf::RectangleShape(sf::Vector2f(200, 100));
			button.setPosition(windowWidth / 2 - 100, windowHeight / 2 + 100 * (i - first));
			mainMenuTexture.draw(button);

			textBrush.setString(model->levelNames.at(i));
			textBrush.setPosition(windowWidth / 2 - 75, windowHeight / 2 + 100 * (i - first) + 25);
			mainMenuTexture.draw(textBrush);
		}

		sf::RectangleShape select = sf::RectangleShape(sf::Vector2f(200, 100));
		select.setPosition(windowWidth / 2 - 100, windowHeight / 2 + 100 * (model->mainMenu.getCurSelect() - first));
		select.setFillColor(sf::Color::Transparent);
		select.setOutlineThickness(5);
		select.setOutlineColor(sf::Color::Black);
		mainMenuTexture.draw(select);
	}

	mainMenuTexture.display();
}

void Render::renderWin() {
	sf::Sprite sprite;
	sprite.setTexture(manager.loadTexture("UI/HealthBox"));
	sprite.setScale(200.0 / (float)sprite.getTextureRect().width, 50.0 / (float)sprite.getTextureRect().height);
	sprite.setPosition(windowWidth / 2 - 100, windowHeight / 2 - 15);
	UITexture.draw(sprite);

	textBrush.setString("Level Complete\nPressSpace to Continue");
	textBrush.setPosition(sf::Vector2f(windowWidth / 2 - 75, windowHeight / 2 - 15));
	UITexture.draw(textBrush);
}