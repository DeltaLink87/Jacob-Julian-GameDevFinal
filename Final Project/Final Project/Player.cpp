#include "Player.h"
#include "Projectile.h"
#include "MeleeAttack.h";

#include <iostream>


Player::Player() : Actor(400, 300, 20, 20) {
	maxHealth = curHealth = 50;
}


Player::~Player() { }

void Player::update(float deltaTime) {
	//position.x += velocity.x * deltaTime;
	//position.y += velocity.y * deltaTime;
	//std::cout << curHealth << std::endl;

	//moving the player horizontally
	if (left)
		velocity.x = -200;
	else if (right)
		velocity.x = 200;
	else velocity.x = 0;

	//making the player jump if nessecary
	if (jump) {
		velocity.y = -150;
		climbing = false;
	}

	//checks if player is next to something climbable and begins climbing if up is pressed
	if (up && nextToClimbable)
		climbing = true;
	else if (!nextToClimbable)
		climbing = false;

	//if climbing, changing y velocity based on input
	if (climbing) {
		if (up)
			velocity.y = -100;
		else if (down)
			velocity.y = 100;
		else velocity.y = 0;
	}

	//creating a new attack from the player if instructed to 
	attack = pressAttack;
	attackTimer -= deltaTime;
	if (attack && attackTimer <= 0) {
		attackTimer = 0.5;
		float dirLooking = atan((looking.y - position.y) / (looking.x - position.x));
		if (looking.x - position.x < 0)
			dirLooking += 2 * acos(0);
		//making either a melee attack or projectile attack
		//newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
		if (inventory.count("Dagger") != 0)
			newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
		else newAttacks.push_back(new Projectile(position.x, position.y, 10, 10, sf::Vector2f(200 * cos(dirLooking), 200 * sin(dirLooking)), this));
	}

	//changing the sound timer and horizontal movement based on running or sneaking
	if (velocity.x != 0) {
		if (moveFast) {
			stepSoundTimer -= deltaTime * 2;
			velocity.x *= 2;
		}
		else if (moveSlow) {
			stepSoundTimer -= deltaTime / 2;
			velocity.x /= 2;
		}
		else stepSoundTimer -= deltaTime;
	}
	else stepSoundTimer = 0.5;

	//creating new sound as nessesary
	if (stepSoundTimer < 0) {
		//std::cout << "sound" << std::endl;
		stepSoundTimer = 0.5;
		//adjusting loudness of sound based on how fast moving
		float loudness = 200;
		if (moveFast)
			loudness *= 2;
		else if (moveSlow)
			loudness /= 2;
		//creating new sound
		newSounds.push_back(Sound(position.x, position.y, loudness, 0.5, false));
	}

	//updating player location
	position += velocity * deltaTime;

	if (!climbing) {
		//adding gravity to player if not climbing
		velocity.y += 200 * deltaTime;
		if (velocity.y > 200)
			velocity.y = 200;
	}

	//updating player ditbox
	hitBox.setPosition(position);
	nextToClimbable = false;
}

void Player::isAttacking(bool value) { attack = value; }

std::map<std::string, Item*>*  Player::getInventory() { return &inventory; }

bool Player::craftItem(Item* item) {
	for (std::map<std::string, int>::iterator i = item->recipe.begin(); i != item->recipe.end(); i++) {
		if (inventory.count((*i).first) == 0)
			return false;
	}

	for (std::map<std::string, int>::iterator i = item->recipe.begin(); i != item->recipe.end(); i++) {
		//Item* removedItem = (inventory.find((*i).first))->second;
		inventory.erase(inventory.find((*i).first));
		//delete removedItem;
	}
	addInventory(item);

	return true;
}