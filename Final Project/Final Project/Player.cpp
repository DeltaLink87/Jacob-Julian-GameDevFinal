#include "Player.h"
#include "Projectile.h"
#include "MeleeAttack.h";

#include <iostream>


Player::Player(int x, int y) : Actor(x, y, 20, 20) {
	maxHealth = curHealth = 50;
	isPlayer = true;
	textureName = "Actors/Player";
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
	if (jump && onGround) {
		velocity.y = -150;
		climbing = false;
		onGround = false;
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

	if (!climbing) {
		//adding gravity to player if not climbing
		velocity.y += 200 * deltaTime;
		if (velocity.y > 200)
			velocity.y = 200;
	}

	curItemSelected = (curItemSelected - scroll + inventory.getHeight()) % inventory.getHeight();

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
		Item* weapon = inventory.getCurSeletected(curItemSelected);
		if (weapon == NULL)
			newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
		else if (weapon->attackType == 0)
			newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
		else newAttacks.push_back(new Projectile(position.x, position.y, 10, 10, sf::Vector2f(200 * cos(dirLooking), 200 * sin(dirLooking)), this));
	}

	//changing the sound timer and horizontal movement based on running or sneaking
	if (velocity.x != 0 && onGround) {
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
		float loudness = 100;
		if (moveFast)
			loudness *= 2;
		else if (moveSlow)
			loudness /= 2;
		//creating new sound
		newSounds.push_back(Sound(position.x + hitBox.getSize().x / 2, position.y + hitBox.getSize().y, loudness, 0.5, false));
	}

	//updating player location
	position += velocity * deltaTime;

	//updating player ditbox
	hitBox.setPosition(position);
	nextToClimbable = false;
	onGround = false;
}

void Player::isAttacking(bool value) { attack = value; }

Inventory*  Player::getInventory() { return &inventory; }

bool Player::craftItem(Item* item) {
	return inventory.craft(item);
}