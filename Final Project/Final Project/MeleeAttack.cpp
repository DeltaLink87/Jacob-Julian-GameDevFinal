#include "MeleeAttack.h"


//Will create a pre-Constructor for melee attack that takes an int to set type then calls the default meleeattack constructor
MeleeAttack::MeleeAttack(int x, int y, int width, int height, float dir, Actor* newSource, Item* item) : Attack(x, y, width, height, newSource) {

	this->melee = true;
	this->spritePositionSet = true;

	//setting attack variables based on item stats is item is provided, else creating defualt stats
	if (item != NULL) {
		this->type = item->getAttackType() + 1;
		damage = item->getAttack();

		if (item->dimPreset) {
			this->spriteWidth = item->presetItemDimX;
			this->spriteHeight = item->presetItemDimY;
		}

		this->textureName = "Attacks/" + item->getName() + "AttackImage";

		canAssassinate = item->getCanAssassinate();
	}
	else {	//setting variables to defualt if no item given
		this->type = 2;

		this->spriteWidth = 10;
		this->spriteHeight = 10;

		this->textureName = "Attacks/DaggerAttackImage";
	}

	//initilizing variables for a stabbing attack
	if (this->type == DAGGER) {

		direction = dir;
		type = 1;
		thrust = true;
		anchor = newSource->getPosition();

		attackMotion = 0.1;
		

	}
	//initilizing variables for a swinging attack
	else if (this->type == SWORD) {

		if (newSource->isFacingRight()) {
			this->sprite.setScale(sf::Vector2f(.15, .2));

			direction = dir - ((120.0 / 180.0) * pi);
		}
		else {
			this->sprite.setScale(sf::Vector2f(.15, -.2));

			direction = dir + ((120.0 / 180.0) * pi);

		}
		type = 2;
		anchor = newSource->getPosition();
	}
}



//Alternate constructor with a type differentiator at the end, used to determine attack behavior.
MeleeAttack::MeleeAttack(int x, int y, int width, int height, float dir, Actor* newSource, int t) : Attack(x, y, width, height, newSource) {
	this->type = t;
	this->melee = true;
	if (this->type == DAGGER) {


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


			this->sprite.setScale(sf::Vector2f(.15, -.2));

			direction = dir - ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			anchor = newSource->getPosition();
		}
		else {

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
		//checking if collided with wall or done motion
		if (attackMotion >= 1 || collidedWithTile) {
			thrust = false;
		}
		//calculating new position of attack
		position.x = source->getPosition().x + source->getHitBox().getSize().x / 4 + source->getHitBox().getSize().x * cos(direction) * attackMotion * 1;
		position.y = source->getPosition().y + source->getHitBox().getSize().y / 4 + source->getHitBox().getSize().y * sin(direction) * attackMotion * 1;

		//adding time to motion timer
		if (thrust)
			attackMotion += deltaTime * 2;
		else
			attackMotion -= deltaTime * 2;

		duration += deltaTime;

		//checking if attack is done
		if (attackMotion <= 0)
			remove();

		
	}
  
	//Update for "swing" type weapons
	else if (this->type == SWORD) {
		//checking if collided with wall or done motion
		if (collidedWithTile && duration < 1.8) {
			duration = 1.8;
		}

		//checking if attack is still swinging and changing direction if it is
		if (duration > 1.3 && duration < 1.5) {
			if (source->isFacingRight())
				direction += deltaTime * ((1.0 / 3.0) * pi) * 10;
			else
				direction -= deltaTime * ((1.0 / 3.0) * pi) * 10;
		}

		duration += deltaTime;

		//updating position of the attack
		position.x = source->getPosition().x + source->getHitBox().getSize().x / 2 + source->getHitBox().getSize().x * cos(direction);
		position.y = source->getPosition().y + source->getHitBox().getSize().y / 2 + source->getHitBox().getSize().y * sin(direction);

		//checking if attack is done
		if (duration >= 2.0)
			remove();
	}

	//setting sprite position and rotation
	this->sprite.setPosition(position);
	rotation(direction);

	//calculating the hitbox size and position for this attack
	hitBox = sf::RectangleShape(sf::Vector2f(abs(cos(direction) * spriteWidth) + abs(sin(direction) * spriteHeight), abs(cos(direction) * spriteHeight) + abs(sin(direction) * spriteWidth)));
	hitBox.setFillColor(sf::Color::Blue);
	//calculating the x,y coordinates of the hitbox by finding the left-most and top-most x and y coordinate from all the corners of the box
	float angle = atan((float)spriteHeight / (float)spriteWidth);
	float disToFarCorner = sqrt(pow(spriteWidth, 2) + pow(spriteHeight, 2));
	sf::Vector2f corner1(cos(direction) * spriteWidth, sin(direction) * spriteWidth);
	sf::Vector2f corner2(cos(direction + angle) * disToFarCorner, sin(direction + angle) * disToFarCorner);
	 sf::Vector2f corner3(cos(direction + acos(0)) * spriteHeight, sin(direction + acos(0)) * spriteHeight);
	spritePositionDifference = sf::Vector2f(std::min(std::min(.0f, corner1.x), std::min(corner2.x, corner3.x)), std::min(std::min(.0f, corner1.y), std::min(corner2.y, corner3.y)));

	hitBox.setPosition(position + spritePositionDifference);
}


void MeleeAttack::hitTile(Tile* tile){}
