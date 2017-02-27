#include "Player.h"



Player::Player() : Entity(400, 300, 20, 20) {

}


Player::~Player() { }

void Player::update(float deltaTime) {
	//position.x += velocity.x * deltaTime;
	//position.y += velocity.y * deltaTime;
	if (jump)
		velocity.y = -200;

	position += velocity * deltaTime;
	velocity.y += 50 * deltaTime;
	if (velocity.y > 100)
		velocity.y = 100;
	hitBox.setPosition(position);
	//additional changes
}

void Player::hit(Entity* hitThis) {

}

//items = { new Item("name", HashMap<Integer, Integer>{2:1, 3:2}),
//		new Item("name2", HashMap<Integer, Integer>{2:1, 3 : 2}), }