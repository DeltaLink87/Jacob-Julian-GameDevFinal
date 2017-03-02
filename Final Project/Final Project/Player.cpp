#include "Player.h"
#include "Projectile.h"
#include "MeleeAttack.h";

#include <iostream>


Player::Player() : Actor(400, 300, 20, 20) {

}


Player::~Player() { }

void Player::update(float deltaTime) {
	//position.x += velocity.x * deltaTime;
	//position.y += velocity.y * deltaTime;
	//moving the player horizontally
	if (left)
		velocity.x = -100;
	else if (right)
		velocity.x = 100;
	else velocity.x = 0;

	//making the player jump if nessecary
	if (jump)
		velocity.y = -150;

	//creating a new attack from the player if instructed to 
	if (attack) {
		float dir = atan((looking.y - position.y) / (looking.x - position.x));
		if (looking.x - position.x < 0)
			dir += 2 * acos(0);
		//making either a melee attack or projectile attack
		//newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dir, this));
		newAttacks.push_back(new Projectile(position.x, position.y, 10, 10, sf::Vector2f(200 * cos(dir), 200 * sin(dir)), this));
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

	//adding gravity to player
	velocity.y += 200 * deltaTime;
	if (velocity.y > 200)
		velocity.y = 200;

	//updating player ditbox
	hitBox.setPosition(position);
}

void Player::hit(Entity* hitThis) {

}