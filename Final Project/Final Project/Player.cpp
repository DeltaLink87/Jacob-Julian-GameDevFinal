#include "Player.h"
#include "Projectile.h"
#include "MeleeAttack.h";

#include <iostream>


Player::Player(int x, int y) : Actor(x, y, 20, 20) {
	maxHealth = curHealth = 10;
	isPlayer = true;
	textureName = "Actors/Player";
}


Player::~Player() { }

void Player::update(float deltaTime) {
	//position.x += velocity.x * deltaTime;
	//position.y += velocity.y * deltaTime;
	//std::cout << curHealth << std::endl;

	//moving the player horizontally
	if (left) {
		velocity.x = -200;
		if (!isRunning) {
			animationTimer = 0;
			isRunning = true;
		}
		facingRight = false;
	}
	else if (right) {
		velocity.x = 200;		
		if (!isRunning) {
			animationTimer = 0;
			isRunning = true;
		}
		facingRight = true;
	}
	else {		
		velocity.x = 0;
		if (isRunning) {
			animationTimer = 0;
			isIdle = true;
			isRunning = false;
		}
	}
	//making the player jump if nessecary
	if (jump && (onGround || climbing)) {
		velocity.y = -350;
		climbing = false;
		onGround = false;
		isJumping = true;
		animationTimer = 0;
	}

	//checks if player is next to something climbable and begins climbing if up is pressed
	if (up && nextToClimbable) {
		climbing = true;
		isJumping = false;
		isRunning = false;
		if (!isClimbing)
			animationTimer = 0;
	}
	else if (!nextToClimbable) {
		if (climbing)
			velocity.y = 0;
		climbing = false;
	}

	if (down) {
		droppedDown = true;
		if (nextToClimbable)
			climbing = true;
	}
	else droppedDown = false;

	//if climbing, changing y velocity based on input
	if (climbing) {
		if (up)
			velocity.y = -100;
		else if (down)
			velocity.y = 100;
		else velocity.y = 0;
	}

	if (!climbing) {
		//adding gravity to player if not climbing
		velocity.y += 900 * deltaTime;
		if (velocity.y > 400)
			velocity.y = 400;
	}

	curItemSelected = (curItemSelected - scroll + inventory.getHeight()) % inventory.getHeight();

	if (mouse2) {
		std::cout << "Use Item : " << curItemSelected << std::endl;
		Item* curItem = inventory.getCurSeletected(curItemSelected);
		std::cout << curItem << std::endl;
		if (curItem != NULL) {
			bool removeAfterUse = curItem->useItem(this);
			//std::cout << removeAfterUse << std::endl;
			if (removeAfterUse)
				delete inventory.dropItem(0, curItemSelected);
		}
	}

	//creating a new attack from the player if instructed to 
	attack = pressAttack;
	attackTimer -= deltaTime;
	if (attack && attackTimer <= 0) {
		attackTimer = 2.0;
		float mouseLooking = atan((looking.y - position.y) / (looking.x - position.x));
		if (looking.x - position.x < 0)
			mouseLooking += 2 * acos(0);
    
		if (this->looking.x > this->position.x)
			facingRight = true;
		else
			facingRight = false;
    
		Item* weapon = inventory.getCurSeletected(curItemSelected);
		if (weapon == NULL)
			//newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
			newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, mouseLooking, this, weapon));
		else if (weapon->getAttackType() == 0 || weapon->getAttackType() == 1)
			//newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
			newAttacks.push_back(new MeleeAttack(position.x + hitBox.getSize().x / 2, position.y + hitBox.getSize().y / 2, 10, 10, mouseLooking, this, weapon));
		else
			//newAttacks.push_back(new Projectile(position.x, position.y, 10, 10, sf::Vector2f(200 * cos(dirLooking), 200 * sin(dirLooking)), this));
			newAttacks.push_back(new Projectile(position.x + hitBox.getSize().x / 2, position.y + hitBox.getSize().y / 2, 10, 10, sf::Vector2f(200 * cos(mouseLooking), 200 * sin(mouseLooking)), this, weapon));
	}

	attack = pressAttack;
	attackTimer -= deltaTime;
	if (mouseLessAttack && attackTimer <= 0) {
		attackTimer = 2.0;

		Item* weapon = inventory.getCurSeletected(curItemSelected);
		if (weapon == NULL)
			//newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
			newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this, weapon));
		else if (weapon->getAttackType() == 0 || weapon->getAttackType() == 1)
			//newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
			newAttacks.push_back(new MeleeAttack(position.x + hitBox.getSize().x / 2, position.y + hitBox.getSize().y / 2, 10, 10, dirLooking, this, weapon));
		else
			//newAttacks.push_back(new Projectile(position.x, position.y, 10, 10, sf::Vector2f(200 * cos(dirLooking), 200 * sin(dirLooking)), this));
			newAttacks.push_back(new Projectile(position.x + hitBox.getSize().x / 2, position.y + hitBox.getSize().y / 2, 10, 10, sf::Vector2f(200 * cos(dirLooking), 200 * sin(dirLooking)), this, weapon));
	}

	inputTimer -= deltaTime;
	if (inputTimer <= 0) {
		if (scrollLeft)
			curItemSelected = (curItemSelected - 1 + inventory.getHeight()) % inventory.getHeight();
		else if (scrollRight)
			curItemSelected = (curItemSelected + 1) % inventory.getHeight();

		if (scrollLeft || scrollRight)
			inputTimer = 0.1;
	}

	/*
	changing the sound timer and horizontal movement based on running or sneaking
	As well as the amount of deltaTime added to animationTimer based on the player's movement speed
	improving the animation's accuracy.
	*/
	if (velocity.x != 0 && onGround) {
		if (moveFast) {
			stepSoundTimer -= deltaTime * 2;
			velocity.x *= 2;

			//Double of the normal fixed ratio of deltaTime to be added is subtracted here, doubling the animation's incrementation speed
			animationTimer += deltaTime * 10; 
		}
		else if (moveSlow) {
			stepSoundTimer -= deltaTime / 2;
			velocity.x /= 2;

			//Half of the normal fixed ratio of deltaTime to be added is subtracted here, halving the animation's incrementation speed
			animationTimer -= deltaTime * 5; 
		}
		else stepSoundTimer -= deltaTime;
	}
	else stepSoundTimer = 0.5;

	//creating new sound as nessesary
	if (stepSoundTimer < 0) {
		//std::cout << "sound" << std::endl;
		stepSoundTimer = 0.5;
		//adjusting loudness of sound based on how fast moving
		float loudness = 100;
		if (moveFast)
			loudness *= 2;
		else if (moveSlow)
			loudness = hitBox.getSize().x / 4;
		//creating new sound
		newSounds.push_back(Sound(position.x + hitBox.getSize().x / 2, position.y + hitBox.getSize().y / 2, loudness, 0.5, false));
	}

	if (velocity.x != 0) {
		dirLooking = atan(velocity.y / velocity.x);
		if (velocity.x < 0)
			dirLooking += 2 * acos(0);
	}
	else if (velocity.y > 200 * deltaTime * 2)
		dirLooking = acos(0);
	else if (velocity.y < 0)
		dirLooking = 3 * acos(0);

	//updating player location
	position += velocity * deltaTime;

	//The fixed ratio of deltaTime added to animationTimer
	animationTimer += deltaTime * 10; 

	//updating player ditbox
	hitBox.setPosition(position);
	nextToClimbable = false;
	onGround = false;
	isClimbing = climbing;

	//std::cout << damageFlicker << std::endl;
	if (damageFlicker > 0) {
		damageFlicker--;
		if ((int)(damageFlicker / 2) % 2 == 0)
			displaySprite = true;
		else displaySprite = false;
	}
	else displaySprite = true;
}

void Player::isAttacking(bool value) { attack = value; }

int Player::getCurSelected() { return curItemSelected; }

bool Player::craftItem(Item* item) {
	return inventory.craft(item);
}