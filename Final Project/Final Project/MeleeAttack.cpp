#include "MeleeAttack.h"


//Will create a pre-Constructor for melee attack that takes an int to set type then calls the default meleeattack constructor
MeleeAttack::MeleeAttack(int x, int y, int width, int height, float dir, Actor* newSource, Item* item) : Attack(x, y, width, height, newSource) {
	
	if (item != NULL)
		this->type = item->attackType + 1;
	else 
		this->type = 2;

	this->melee = true;
	this->spritePositionSet = true;

	if (item->dimPreset) {
		this->spriteWidth = item->presetItemDimX;
		this->spriteHeight = item->presetItemDimY;
	}


	if (this->type == DAGGER) {
		/*
		 --TEMP--
			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			if (newSource->isFacingRight())
				this->visualRepresentation.setScale(sf::Vector2f(.15, .2));
			else
				this->visualRepresentation.setScale(sf::Vector2f(-.15, .2));

			//std::cout << ((float) this->visualRepresentation.getLocalBounds().height) * this->visualRepresentation.getScale().y << std::endl;

			this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
		*/

		/*
		if (item != NULL)
			this->textureName = "Attacks/" + item->name + "AttackImage";
		else this->textureName = "Attacks/DaggerAttackImage";
		*/

		this->textureName = "Attacks/iconToImgTEST";
		



		//if (newSource->isFacingRight())
		//	this->sprite.setScale(sf::Vector2f(.15, .2));
		//else
		//	this->sprite.setScale(sf::Vector2f(-.15, .2));
    
    
		//this->getHitBox().setSize(sf::Vector2f(this->sprite.getLocalBounds().width * this->sprite.getScale().x, this->sprite.getLocalBounds().height * this->sprite.getScale().y));
		//this->getHitBox().setSize(sf::Vector2f(30,10));
    
		direction = dir;
		type = 1;
		thrust = true;
		anchor = newSource->getPosition();

		attackMotion = 0.1;
		

	}

	else if (this->type == SWORD) {

		if (item != NULL)
			this->textureName = "Attacks/" + item->name + "AttackImage";
		else this->textureName = "Attacks/DaggerAttackImage";

		if (newSource->isFacingRight()) {
			/* --TEMP--
				  this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
				  this->visualRepresentation.setTexture(textureOfVisualRepresentation);
				  this->visualRepresentation.setScale(sf::Vector2f(.15, .2));



				  //this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
				  //this->sprite.setSize(this->getHitBox().getSize());
			*/

			this->sprite.setScale(sf::Vector2f(.15, .2));

			direction = dir - ((120.0 / 180.0) * pi);
		}
		else {
			/*
			--TEMP--
					  this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
					  this->visualRepresentation.setTexture(textureOfVisualRepresentation);
					  this->visualRepresentation.setScale(sf::Vector2f(.15, -.2));


					  //this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
					  //this->sprite.setSize(this->getHitBox().getSize());
				*/

			this->sprite.setScale(sf::Vector2f(.15, -.2));

			direction = dir + ((120.0 / 180.0) * pi);

		}
		type = 2;
		anchor = newSource->getPosition();




	}
	if (item != NULL)
		canAssassinate = item->canAssassinate;
}



//Alternate constructor with a type differentiator at the end, used to determine attack behavior.
MeleeAttack::MeleeAttack(int x, int y, int width, int height, float dir, Actor* newSource, int t) : Attack(x, y, width, height, newSource) {
	this->type = t;
	this->melee = true;
	if (this->type == DAGGER) {
		/*
		--TEMP--
		this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
		this->visualRepresentation.setTexture(textureOfVisualRepresentation);
		if (newSource->isFacingRight())
		this->visualRepresentation.setScale(sf::Vector2f(.15, .2));
		else
		this->visualRepresentation.setScale(sf::Vector2f(-.15, .2));

		//std::cout << ((float) this->visualRepresentation.getLocalBounds().height) * this->visualRepresentation.getScale().y << std::endl;

		this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
		*/

		this->textureName = "Items/DaggerAttackImage";

		if (newSource->isFacingRight())
			this->sprite.setScale(sf::Vector2f(.15, .2));
		else
			this->sprite.setScale(sf::Vector2f(-.15, .2));


		//this->getHitBox().setSize(sf::Vector2f(this->sprite.getLocalBounds().width * this->sprite.getScale().x, this->sprite.getLocalBounds().height * this->sprite.getScale().y));
		this->getHitBox().setSize(sf::Vector2f(30,10));

		direction = dir;
		type = 1;
		thrust = true;
		anchor = newSource->getPosition();

		attackMotion = 0.1;


	}

	else if (this->type == SWORD) {

		this->textureName = "Items/DaggerAttackImage";

		if (newSource->isFacingRight()) {
			/*
			--TEMP--
			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			this->visualRepresentation.setScale(sf::Vector2f(.15, .2));



			//this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
			//this->sprite.setSize(this->getHitBox().getSize());
			*/

			this->sprite.setScale(sf::Vector2f(.15, -.2));

			direction = dir - ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			anchor = newSource->getPosition();
		}
		else {
			/*
			--TEMP--
			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			this->visualRepresentation.setScale(sf::Vector2f(.15, -.2));


			//this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
			//this->sprite.setSize(this->getHitBox().getSize());
			*/
			direction = dir + ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			anchor = newSource->getPosition();



		}

	}
	//canAssassinate = item->canAssassinate;
}




MeleeAttack::~MeleeAttack() { }

void MeleeAttack::update(float deltaTime) {
	bool check = this->isRemoved();

	if (this->isRemoved()) {
		return;
	}

	//Update for thrust/stab type weapons
	else if (this->type == DAGGER) {

		if (attackMotion >= 1 || collidedWithTile) {
			thrust = false;
		}

		position.x = source->getPosition().x + source->getHitBox().getSize().x / 4 + source->getHitBox().getSize().x * cos(direction) * attackMotion * 1;
		position.y = source->getPosition().y + source->getHitBox().getSize().y / 4 + source->getHitBox().getSize().y * sin(direction) * attackMotion * 1;

		if (thrust)
			attackMotion += deltaTime * 2;
		else
			attackMotion -= deltaTime * 2;

		duration += deltaTime;

		//if (duration >= 2.0)
		if (attackMotion <= 0)
			remove();


		this->sprite.setPosition(position);
    //rotation needs to be changed to sprite --TEMP--
		rotation(direction);
		hitBox = sf::RectangleShape(sf::Vector2f(abs(cos(direction) * spriteWidth) + abs(sin(direction) * spriteHeight), abs(cos(direction) * spriteHeight) + abs(sin(direction) * spriteWidth)));
		hitBox.setFillColor(sf::Color::Blue);

		float angle = atan((float)spriteHeight / (float)spriteWidth);
		float disToFarCorner = sqrt(pow(spriteWidth, 2) + pow(spriteHeight, 2));
		sf::Vector2f corner1(cos(direction) * spriteWidth, sin(direction) * spriteWidth);
		sf::Vector2f corner2(cos(direction + angle) * disToFarCorner, sin(direction + angle) * disToFarCorner);
		sf::Vector2f corner3(cos(direction + acos(0)) * spriteHeight, sin(direction + acos(0)) * spriteHeight);
		spritePositionDifference = sf::Vector2f(std::min(std::min(.0f, corner1.x), std::min(corner2.x, corner3.x)), std::min(std::min(.0f, corner1.y), std::min(corner2.y, corner3.y)));

		hitBox.setPosition(position + spritePositionDifference);
	}
  
  //Update for "swing" type weapons
  else if (this->type == SWORD) {

		if (collidedWithTile && duration < 1.8) {
			duration = 1.8;
		}


		if (duration > 1.3 && duration < 1.5) {
			if (source->isFacingRight())
				direction += deltaTime * ((1.0 / 3.0) * pi) * 10;
			else
				direction -= deltaTime * ((1.0 / 3.0) * pi) * 10;
		}

		duration += deltaTime;

		position.x = source->getPosition().x + source->getHitBox().getSize().x / 2 + source->getHitBox().getSize().x * cos(direction);
		position.y = source->getPosition().y + source->getHitBox().getSize().y / 2 + source->getHitBox().getSize().y * sin(direction);

		this->sprite.setPosition(position);
    
    //rotation needs to be changed to sprite --TEMP--
		rotation(direction);

		//position.x += cos(direction) * 20;
		//position.y += sin(direction) * 20;

		if (duration >= 2.0)
			remove();

		hitBox = sf::RectangleShape(sf::Vector2f(abs(cos(direction) * spriteWidth) + abs(sin(direction) * spriteHeight), abs(cos(direction) * spriteHeight) + abs(sin(direction) * spriteWidth)));
		hitBox.setFillColor(sf::Color::Blue);

		float angle = atan((float)spriteHeight / (float)spriteWidth);
		float disToFarCorner = sqrt(pow(spriteWidth, 2) + pow(spriteHeight, 2));
		sf::Vector2f corner1(cos(direction) * spriteWidth, sin(direction) * spriteWidth);
		sf::Vector2f corner2(cos(direction + angle) * disToFarCorner, sin(direction + angle) * disToFarCorner);
		sf::Vector2f corner3(cos(direction + acos(0)) * spriteHeight, sin(direction + acos(0)) * spriteHeight);
		spritePositionDifference = sf::Vector2f(std::min(std::min(.0f, corner1.x), std::min(corner2.x, corner3.x)), std::min(std::min(.0f, corner1.y), std::min(corner2.y, corner3.y)));

		hitBox.setPosition(position + spritePositionDifference);
	}
}


void MeleeAttack::hitTile(Tile* tile){}
