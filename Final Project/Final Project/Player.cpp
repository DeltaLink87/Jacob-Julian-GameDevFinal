#include "Player.h"



Player::Player() : Entity(400, 300, 20, 20) {

}


Player::~Player() { }

void Player::update(float deltaTime) {
	//position.x += velocity.x * deltaTime;
	//position.y += velocity.y * deltaTime;
	position += velocity * deltaTime;
	position.y += 50 * deltaTime;
	//more changes
	hitBox.setPosition(position);
	//additional changes
}

void Player::hit(Entity* hitThis) {

}