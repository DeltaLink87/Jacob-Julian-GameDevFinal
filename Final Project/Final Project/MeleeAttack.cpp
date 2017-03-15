#include "MeleeAttack.h"



MeleeAttack::MeleeAttack(int x, int y, int width, int height, float dir, Actor* newSource) : Attack(x, y, width, height, newSource) {
	
	this->type = 2;
	this->melee = true;
	if (this->type == DAGGER) {

		this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
		this->visualRepresentation.setTexture(textureOfVisualRepresentation);
		if (newSource->isFacingRight())
			this->visualRepresentation.setScale(sf::Vector2f(.15, .2));
		else
			this->visualRepresentation.setScale(sf::Vector2f(-.15, .2));

		//std::cout << ((float) this->visualRepresentation.getLocalBounds().height) * this->visualRepresentation.getScale().y << std::endl;

		this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
		this->sprite.setSize(this->getHitBox().getSize());
		direction = dir;
		type = 1;
		thrust = true;
		anchor = newSource->getPosition();

		attackMotion = 0.1;
		

	}

	else if (this->type == SWORD) {
		if (newSource->isFacingRight()) {
			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			this->visualRepresentation.setScale(sf::Vector2f(.15, .2));

			//this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
			//this->sprite.setSize(this->getHitBox().getSize());

			direction = dir - ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			thrust = true;
			anchor = newSource->getPosition();
		}
		else {

			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			this->visualRepresentation.setScale(sf::Vector2f(.15, -.2));

			//this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
			//this->sprite.setSize(this->getHitBox().getSize());

			direction = dir + ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			thrust = true;
			anchor = newSource->getPosition();



		}

	}

}


MeleeAttack::MeleeAttack(int x, int y, int width, int height, float dir, Actor* newSource, int t) : Attack(x, y, width, height, newSource) {
	this->type = t;
	this->melee = true;
	if (this->type == DAGGER) {

		this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
		this->visualRepresentation.setTexture(textureOfVisualRepresentation);
		if (newSource->isFacingRight())
			this->visualRepresentation.setScale(sf::Vector2f(.15, .2));
		else
			this->visualRepresentation.setScale(sf::Vector2f(-.15, .2));

		//std::cout << ((float) this->visualRepresentation.getLocalBounds().height) * this->visualRepresentation.getScale().y << std::endl;

		this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
		this->sprite.setSize(this->getHitBox().getSize());
		direction = dir;
		type = 1;
		thrust = true;
		anchor = newSource->getPosition();

		attackMotion = 0.1;


	}

	else if (this->type == SWORD) {
		if (newSource->isFacingRight()) {
			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			this->visualRepresentation.setScale(sf::Vector2f(.15, .2));

			//this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
			//this->sprite.setSize(this->getHitBox().getSize());

			direction = dir - ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			anchor = newSource->getPosition();
		}
		else {

			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			this->visualRepresentation.setScale(sf::Vector2f(.15, -.2));

			//this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
			//this->sprite.setSize(this->getHitBox().getSize());

			direction = dir + ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			anchor = newSource->getPosition();



		}

	}

}



MeleeAttack::~MeleeAttack() { }

void MeleeAttack::update(float deltaTime) {
	bool check = this->isRemoved();

	if (this->isRemoved()) {
		return;
	}

	//Update for swing type weapons 

	
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

		if (duration >= 2.0)
			remove();


		this->visualRepresentation.setPosition(position);
		rotation(direction);
		hitBox.setPosition(position);
	}

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

		this->visualRepresentation.setPosition(position);
		rotation(direction);

		position.x += cos(direction) * 20;
		position.y += sin(direction) * 20;

		if (duration >= 2.0)
			remove();

		hitBox.setPosition(position);
	}
}

/*
void MeleeAttack::motion(float deltaTime) {


	if (this->type == DAGGER) {
		if ((pow(this->position.x - source->getPosition().x, 2) + pow(this->position.y - source->getPosition().y, 2)) > 32) {
			thrust = false;
		}
		if (thrust) {
			this->position.x += cos(direction);
			this->position.y += sin(direction);
		}

	}


}


void MeleeAttack::syncAnchor(float deltaTime) {
	if (this->anchor != source->getPosition)



}
*/