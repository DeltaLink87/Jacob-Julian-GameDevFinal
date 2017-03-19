#include "Render.h"
#include <sstream>
#include <algorithm>
#include <string>
#include <exception>


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


	
	playerSpriteSheet.loadFromFile("Assets/Textures/Actors/playerSheet.png");
	enemySpriteSheet.loadFromFile("Assets/Textures/Actors/enemySheet.png");


	this->playerSpriteArray = new sf::Sprite*[4];
	this->playerSpriteArray[0] = new sf::Sprite[3];
	for (int i = 0; i < 3; i++) {
		playerSpriteArray[0][i].setScale(2, 2);
		playerSpriteArray[0][i].setTexture(this->playerSpriteSheet);
		playerSpriteArray[0][i].setTextureRect(sf::IntRect(sf::Vector2i(i * 16, 0), sf::Vector2i(16,16)));
	}
	this->playerSpriteArray[1] = new sf::Sprite[6];

	for (int i = 0; i < 6; i++) {
		playerSpriteArray[1][i].setScale(2, 2);
		playerSpriteArray[1][i].setTexture(this->playerSpriteSheet);
		playerSpriteArray[1][i].setTextureRect(sf::IntRect(sf::Vector2i(i * 16, 16), sf::Vector2i(16, 16)));
	}

	this->playerSpriteArray[2] = new sf::Sprite[3];

	for (int i = 0; i < 3; i++) {
		playerSpriteArray[2][i].setScale(2, 2);
		playerSpriteArray[2][i].setTexture(this->playerSpriteSheet);
		playerSpriteArray[2][i].setTextureRect(sf::IntRect(sf::Vector2i(i * 16, 32), sf::Vector2i(16, 16)));

	}
	
	this->playerSpriteArray[3] = new sf::Sprite[2];

	for (int i = 0; i < 2; i++) {
		playerSpriteArray[3][i].setScale(2, 2);
		playerSpriteArray[3][i].setTexture(this->playerSpriteSheet);
		playerSpriteArray[3][i].setTextureRect(sf::IntRect(sf::Vector2i(i * 16, 48), sf::Vector2i(16, 16)));

	}

	
	this->enemySpriteArray = new sf::Sprite*[4];
	this->enemySpriteArray[0] = new sf::Sprite[3];
	for (int i = 0; i < 3; i++) {
		enemySpriteArray[0][i].setScale(2, 2);
		enemySpriteArray[0][i].setTexture(this->enemySpriteSheet);
		enemySpriteArray[0][i].setTextureRect(sf::IntRect(sf::Vector2i(i * 16, 0), sf::Vector2i(16, 16)));
	}
	this->enemySpriteArray[1] = new sf::Sprite[6];

	for (int i = 0; i < 6; i++) {
		enemySpriteArray[1][i].setScale(2, 2);
		enemySpriteArray[1][i].setTexture(this->enemySpriteSheet);
		enemySpriteArray[1][i].setTextureRect(sf::IntRect(sf::Vector2i(i * 16, 16), sf::Vector2i(16, 16)));
	}

	this->enemySpriteArray[2] = new sf::Sprite[3];

	for (int i = 0; i < 3; i++) {
		enemySpriteArray[2][i].setScale(2, 2);
		enemySpriteArray[2][i].setTexture(this->enemySpriteSheet);
		enemySpriteArray[2][i].setTextureRect(sf::IntRect(sf::Vector2i(i * 16, 32), sf::Vector2i(16, 16)));

	}

	this->enemySpriteArray[3] = new sf::Sprite[2];

	for (int i = 0; i < 2; i++) {
		enemySpriteArray[3][i].setScale(2, 2);
		enemySpriteArray[3][i].setTexture(this->enemySpriteSheet);
		enemySpriteArray[3][i].setTextureRect(sf::IntRect(sf::Vector2i(i * 16, 48), sf::Vector2i(16, 16)));

	}
	
}

Render::~Render(){ }


void Render::renderEnemySpriteArray(Enemy* enemy) {





	if (enemy->isJumping) {

		enemySpriteArray[2][0].setPosition(enemy->getPosition());


		if (!enemy->isFacingRight()) {

			enemySpriteArray[2][0].move(sf::Vector2f(32, 0));

			if (enemySpriteArray[2][0].getScale().x > 0)
				enemySpriteArray[2][0].scale(-1.f, 1.f);
		}
		else if (enemySpriteArray[2][0].getScale().x < 0)
			enemySpriteArray[2][0].scale(-1.f, 1.f);


		enemySpriteArray[2][0].move(sf::Vector2f(-6, -12));
		modelTexture.draw(enemySpriteArray[2][0]);

	}
	else if (enemy->isClimbing) {
		enemySpriteArray[3][((int)enemy->animationTimer / 3) % 2].setPosition(enemy->getPosition());

		if (!enemy->isFacingRight()) {

			enemySpriteArray[3][((int)enemy->animationTimer / 3) % 2].move(sf::Vector2f(32, 0));

			if (enemySpriteArray[3][((int)enemy->animationTimer / 3) % 2].getScale().x > 0)
				enemySpriteArray[3][((int)enemy->animationTimer / 3) % 2].scale(-1.f, 1.f);
		}
		else if (enemySpriteArray[3][((int)enemy->animationTimer / 3) % 2].getScale().x < 0)
			enemySpriteArray[3][((int)enemy->animationTimer / 3) % 2].scale(-1.f, 1.f);

		enemySpriteArray[3][((int)enemy->animationTimer / 3) % 2].move(sf::Vector2f(-6, -12));
		modelTexture.draw(enemySpriteArray[3][((int)enemy->animationTimer / 3) % 2]);

	}
	else if (enemy->isRunning) {

		enemySpriteArray[1][((int)enemy->animationTimer / 2) % 6].setPosition(enemy->getPosition());

		if (!enemy->isFacingRight()) {

			enemySpriteArray[1][((int)enemy->animationTimer / 2) % 6].move(sf::Vector2f(32, 0));

			if (enemySpriteArray[1][((int)enemy->animationTimer / 2) % 6].getScale().x > 0)
				enemySpriteArray[1][((int)enemy->animationTimer / 2) % 6].scale(-1.f, 1.f);
		}
		else if (enemySpriteArray[1][((int)enemy->animationTimer / 2) % 6].getScale().x < 0)
			enemySpriteArray[1][((int)enemy->animationTimer / 2) % 6].scale(-1.f, 1.f);


		enemySpriteArray[1][((int)enemy->animationTimer / 2) % 6].move(sf::Vector2f(-6, -12));
		modelTexture.draw(enemySpriteArray[1][((int)enemy->animationTimer / 2) % 6]);

	}
	else {


		enemySpriteArray[0][((int)enemy->animationTimer / 3) % 3].setPosition(enemy->getPosition());

		if (!enemy->isFacingRight()) {

			enemySpriteArray[0][((int)enemy->animationTimer / 3) % 3].move(sf::Vector2f(32, 0));

			if (enemySpriteArray[0][((int)enemy->animationTimer / 3) % 3].getScale().x > 0)
				enemySpriteArray[0][((int)enemy->animationTimer / 3) % 3].scale(-1.f, 1.f);
		}
		else if (enemySpriteArray[0][((int)enemy->animationTimer / 3) % 3].getScale().x < 0)
			enemySpriteArray[0][((int)enemy->animationTimer / 3) % 3].scale(-1.f, 1.f);


		enemySpriteArray[0][((int)enemy->animationTimer / 3) % 3].move(sf::Vector2f(-6, -12));
		modelTexture.draw(enemySpriteArray[0][((int)enemy->animationTimer / 3) % 3]);

	}


}


//Polish notes: Maybe get the sprite at the start, assign it to a sprite pointer, then do common modifcations on it before then calling draw on the sprite pointer, would save lines of code.
void Render::renderPlayerSpriteArray() {
	
	if (model->player->isJumping) {

		playerSpriteArray[2][0].setPosition(model->player->getPosition());


		if (!model->player->isFacingRight()) {

			playerSpriteArray[2][0].move(sf::Vector2f(32, 0));

			if (playerSpriteArray[2][0].getScale().x > 0)
				playerSpriteArray[2][0].scale(-1.f, 1.f);
		}
		else if (playerSpriteArray[2][0].getScale().x < 0)
			playerSpriteArray[2][0].scale(-1.f, 1.f);


		playerSpriteArray[2][0].move(sf::Vector2f(-6, -12));
		modelTexture.draw(playerSpriteArray[2][0]);

	}
	else if (model->player->isClimbing) {
		playerSpriteArray[3][((int)model->player->animationTimer / 3 ) % 2].setPosition(model->player->getPosition());

		if (!model->player->isFacingRight()) {

			playerSpriteArray[3][((int)model->player->animationTimer / 3) % 2].move(sf::Vector2f(32, 0));

			if (playerSpriteArray[3][((int)model->player->animationTimer / 3) % 2].getScale().x > 0)
				playerSpriteArray[3][((int)model->player->animationTimer / 3) % 2].scale(-1.f, 1.f);
		}
		else if (playerSpriteArray[3][((int)model->player->animationTimer / 3) % 2].getScale().x < 0)
			playerSpriteArray[3][((int)model->player->animationTimer / 3) % 2].scale(-1.f, 1.f);

		playerSpriteArray[3][((int)model->player->animationTimer / 3) % 2].move(sf::Vector2f(-6, -12));
		modelTexture.draw(playerSpriteArray[3][((int)model->player->animationTimer / 3) % 2]);

	}
	else if (model->player->isRunning) {

		playerSpriteArray[1][((int)model->player->animationTimer / 2) % 6].setPosition(model->player->getPosition());

		if (!model->player->isFacingRight()) {

			playerSpriteArray[1][((int)model->player->animationTimer / 2) % 6].move(sf::Vector2f(32, 0));

			if (playerSpriteArray[1][((int)model->player->animationTimer / 2) % 6].getScale().x > 0)
				playerSpriteArray[1][((int)model->player->animationTimer / 2) % 6].scale(-1.f, 1.f);
		}
		else if (playerSpriteArray[1][((int)model->player->animationTimer / 2) % 6].getScale().x < 0)
			playerSpriteArray[1][((int)model->player->animationTimer / 2) % 6].scale(-1.f, 1.f);


		playerSpriteArray[1][((int)model->player->animationTimer / 2) % 6].move(sf::Vector2f(-6, -12));
		modelTexture.draw(playerSpriteArray[1][((int)model->player->animationTimer / 2) % 6]);

	}
	else {


		playerSpriteArray[0][((int)model->player->animationTimer / 3) % 3].setPosition(model->player->getPosition());

		if (!model->player->isFacingRight()) {

			playerSpriteArray[0][((int)model->player->animationTimer / 3) % 3].move(sf::Vector2f(32, 0));

			if (playerSpriteArray[0][((int)model->player->animationTimer / 3) % 3].getScale().x > 0)
				playerSpriteArray[0][((int)model->player->animationTimer / 3) % 3].scale(-1.f, 1.f);
		}
		else if (playerSpriteArray[0][((int)model->player->animationTimer / 3) % 3].getScale().x < 0)
			playerSpriteArray[0][((int)model->player->animationTimer / 3) % 3].scale(-1.f, 1.f);


		playerSpriteArray[0][((int)model->player->animationTimer / 3) % 3].move(sf::Vector2f(-6, -12));
		modelTexture.draw(playerSpriteArray[0][((int)model->player->animationTimer / 3) % 3]);

	}

}

void Render::initializeRenderable(Renderable* renderable) {
	//std::cout << renderable->textureName << std::endl;
	renderable->sprite.setTexture(manager.loadTexture(renderable->textureName));
	renderable->sprite.setScale(sf::Vector2f((float)renderable->spriteWidth / (float)renderable->sprite.getTextureRect().width, (float)renderable->spriteHeight / (float)renderable->sprite.getTextureRect().height));
	renderable->sprite.setPosition(renderable->getPosition());
	renderable->sprite.setRotation(renderable->spriteRotation);
	renderable->spriteInitialized = true;
}

void Render::drawRenderable(sf::RenderTarget& target, Renderable* renderable) {
	if (renderable->displaySprite) {
		if (!renderable->spritePositionSet)
			renderable->sprite.setPosition(renderable->getPosition());
		target.draw(renderable->sprite);
	}
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
	if (model->gameMode == 8) {
		renderLose();
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
	//drawRenderable(modelTexture, model->player);
	if (model->player->displaySprite)
		renderPlayerSpriteArray();

	//rendering enemies
	for (std::vector<Enemy*>::iterator i = model->enemies.begin(); i != model->enemies.end(); i++) {
		if (!(*i)->isRemoved()) {
			if (!(*i)->spriteInitialized)
				initializeRenderable(*i);
			//drawRenderable(modelTexture, *i);
			if ((*i)->displaySprite)
				renderEnemySpriteArray(*i);
			if ((*i)->noticeTimer > 0) {
				sf::RectangleShape notice = sf::RectangleShape(sf::Vector2f(5, 10));
				notice.setPosition((*i)->getPosition().x + 5, (*i)->getPosition().y - 15);
				notice.setFillColor(sf::Color::Red);
				modelTexture.draw(notice);
			}

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
		//modelTexture.draw((*i)->getHitBox());
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

	border = sf::RectangleShape(sf::Vector2f(410, 330));
	border.setPosition(sf::Vector2f(195, 145));
	border.setFillColor(sf::Color::White);
	craftMenuTexture.draw(border);

	center = sf::RectangleShape(sf::Vector2f(400, 320));
	center.setPosition(sf::Vector2f(200, 150));
	center.setFillColor(sf::Color(100, 100, 100));
	craftMenuTexture.draw(center);

	divide = sf::RectangleShape(sf::Vector2f(5, 320));
	divide.setPosition(sf::Vector2f(330, 150));
	divide.setFillColor(sf::Color::White);
	craftMenuTexture.draw(divide);

	textBrush.setString("Items:");
	textBrush.setPosition(sf::Vector2f(205, 150));
	craftMenuTexture.draw(textBrush);

	int counter = 0, firstRender, lastRender;
	if (model->craftMenu->totalItems < 3) {
		firstRender = 0;
		lastRender = model->craftMenu->totalItems;
	}
	else if (model->craftMenu->curSelected > model->craftMenu->totalItems - 2) {
		firstRender = model->craftMenu->totalItems - 3;
		lastRender = model->craftMenu->totalItems;
	}
	else if (model->craftMenu->curSelected < 2) {
		firstRender = 0;
		lastRender = 3;
	}
	else {
		firstRender = model->craftMenu->curSelected - 1;
		lastRender = model->craftMenu->curSelected + 2;
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

	model->craftMenu->selectedBox.setPosition(200, 175 + 75 * (model->craftMenu->curSelected - firstRender));
	craftMenuTexture.draw(model->craftMenu->selectedBox);

	Item* item = model->craftMenu->itemList.at(model->craftMenu->itemNameList.at(model->craftMenu->curSelected));
	if (item->name.length() < 12)
		makeStringTextrue(item->name, 446, 155, 154, 30, craftMenuTexture, 25);
	else
		makeStringTextrue(item->name, 446, 155, 154, 30, craftMenuTexture, 20);

	makeStringTextrue(item->type, 446, 185, 154, 30, craftMenuTexture, 25);
	makeStringTextrue(item->description, 340, 272, 265, 90, craftMenuTexture, 12);

	std::string itemRecipe = "Required: NL ";
	for (std::map<std::string, int>::iterator i = item->recipe.begin(); i != item->recipe.end(); i++) {
		std::stringstream ss;
		ss << i->second;
		itemRecipe += i->first + " X" + ss.str() + " NL ";
	}
	makeStringTextrue(itemRecipe, 340, 363, 265, 90, craftMenuTexture, 12);

	sf::Sprite sprite;
	sprite.setTexture(item->smallIconTexture);
	sprite.setScale(1.5, 1.5);
	sprite.setPosition(335, 150);
	//sprite.setScale(112 / (float)item->smallIconTexture.getSize().x, 117 / (float)item->smallIconTexture.getSize().y);
	craftMenuTexture.draw(sprite);

	//model->craftMenu->itemList.at(model->craftMenu->itemNameList.at(model->craftMenu->curSelected))->menuDescription.setPosition(sf::Vector2f(335, 150));
	//craftMenuTexture.draw(model->craftMenu->itemList.at(model->craftMenu->itemNameList.at(model->craftMenu->curSelected))->menuDescription);

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
		for (int x = -1; x < inv->getWidth(); x++) {
			if (y >= inv->getArmourSlots() && x == -1)
				continue;

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
		makeStringTextrue(item->name, left + 100, top + 5, 150, 30, invMenuTexture, 18);
		makeStringTextrue(item->type, left + 100, top + 35, 150, 30, invMenuTexture, 18);
		makeStringTextrue(item->description, left + 5, top + 100, 220, 90, invMenuTexture, 12);

		std::string itemRecipe = "Required: NL ";
		for (std::map<std::string, int>::iterator i = item->recipe.begin(); i != item->recipe.end(); i++) {
			std::stringstream ss;
			ss << i->second;
			itemRecipe += i->first + " X" + ss.str() + " NL ";
		}
		makeStringTextrue(itemRecipe, left + 5, top + 190, 220, 90, invMenuTexture, 12);

		sf::Sprite sprite;
		sprite.setTexture(item->smallIconTexture);
		sprite.setScale(1.5, 1.5);
		sprite.setPosition(left + 5, top + 5);
		//sprite.setScale(112 / (float)item->smallIconTexture.getSize().x, 117 / (float)item->smallIconTexture.getSize().y);
		invMenuTexture.draw(sprite);

		//item->menuDescription.setPosition(left + 5, top + 5);
		//item->menuDescription.setScale(226.0 / (float)item->menuDescription.getTextureRect().width, 237.0 / (float)item->menuDescription.getTextureRect().height);
		//invMenuTexture.draw(item->menuDescription);
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

	makeStringTextrue("Level Complete NL Press Space to Continue", windowWidth / 2 - 75, windowHeight / 2 - 15, 150, 45, UITexture);
	//makeStringTextrue("TEST test TEST test TEST test TEST test TEST test TEST test TEST test", windowWidth / 2 - 75, windowHeight / 2 - 15, 150, 45, UITexture);
	//textBrush.setString("Game Over\nPress Space to Retry");
	//textBrush.setPosition(sf::Vector2f(windowWidth / 2 - 75, windowHeight / 2 - 15));
	//UITexture.draw(textBrush);
}

void Render::renderLose() {
	sf::Sprite sprite;
	sprite.setTexture(manager.loadTexture("UI/HealthBox"));
	sprite.setScale(200.0 / (float)sprite.getTextureRect().width, 50.0 / (float)sprite.getTextureRect().height);
	sprite.setPosition(windowWidth / 2 - 100, windowHeight / 2 - 15);
	UITexture.draw(sprite);

	makeStringTextrue("Game Over NL Press Space to Retry", windowWidth / 2 - 75, windowHeight / 2 - 15, 150, 45, UITexture);
	//makeStringTextrue("TEST test TEST test TEST test TEST test TEST test TEST test TEST test", windowWidth / 2 - 75, windowHeight / 2 - 15, 150, 45, UITexture);
	//textBrush.setString("Game Over\nPress Space to Retry");
	//textBrush.setPosition(sf::Vector2f(windowWidth / 2 - 75, windowHeight / 2 - 15));
	//UITexture.draw(textBrush);
}

void Render::makeStringTextrue(std::string msg, int x, int y, int width, int height, sf::RenderTarget& target, int fontSize) {
	std::vector<std::string> words;
	std::stringstream ss;
	ss << msg;
	msg = "";
	std::string word, prevWord;
	ss >> word;
	int numOfNewLines = 0;
	while (word.compare(prevWord) != 0) {
		//std::cout << word << std::endl;
		words.push_back(word);
		if (word.compare("NL") == 0)
			numOfNewLines++;
		else msg += word + " ";
		prevWord = word;
		ss >> word;
	}

	sf::Text text;
	std::string totalString = "";
	text.setFont(font);
	text.setFillColor(sf::Color::Black);

	int lineLength = 0;
	if (fontSize == -1) {
		text.setCharacterSize(12);
		text.setString(msg);

		int length = text.getLocalBounds().width;
		float ratio = (float)width / (float)height;
		float scaler = sqrt((float)(length * text.getCharacterSize()) / (width * height));
		//text.setCharacterSize((1 / scaler) * text.getCharacterSize());
		//lineLength = width * scaler;
		lineLength = scaler * width;
		//std::cout << length << "," << lineLength << "," << scaler << "," << ratio << std::endl;
	}
	else {
		lineLength = width;
		text.setCharacterSize(fontSize);
	}


	for (std::vector<std::string>::iterator i = words.begin(); i != words.end(); i++) {
		text.setString(totalString + *i + " ");
		if (i->compare("NL") == 0)
			totalString += "\n";
		else if (text.getLocalBounds().width > lineLength)
			totalString += "\n" + *i + " ";
		else totalString += *i + " ";
	}
	text.setString(totalString);
	if (fontSize == -1) {
		float widthScale = (float)width / (float)(text.getLocalBounds().width + text.getCharacterSize() / 2);
		float heightScale = (float)height / (float)(text.getLocalBounds().height + text.getCharacterSize() / 2);
		//std::cout << widthScale << "," << heightScale << std::endl;
		if (widthScale < heightScale)
			text.setScale(widthScale, widthScale);
		else text.setScale(heightScale, heightScale);
	}
	//std::string thing = text.getString();
	//std::cout << text.getLocalBounds().width << "," << text.getLocalBounds().height << std::endl;
	text.setPosition(0, 0);

	sf::RenderTexture texture;
	texture.create(width, height);
	texture.clear(sf::Color::Transparent);
	texture.draw(text);
	texture.display();
	sf::Sprite sprite;
	sprite.setTexture(texture.getTexture());
	sprite.setPosition(x, y);
	target.draw(sprite);
}