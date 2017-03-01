#include "Enemy.h"



Enemy::Enemy() : Entity(400, 300, 20, 20) {

}

Enemy::Enemy(sf::Vector2f startingPosition) : Entity(400, 300, 20, 20) {

}


Enemy::~Enemy() { }

void Enemy::update(float deltaTime) {
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


void Enemy::update(float deltaTime) {




	position += velocity * deltaTime;
	velocity.y += 50 * deltaTime;
	if (velocity.y > 100)
		velocity.y = 100;
	hitBox.setPosition(position);
}


void Enemy::update(sf::Time deltaTime, sf::Vector2f targetPosition) {

	switch (behaviorState) {

	case 1:

		if (sqrt(pow(homePosition.x - position.x, 2) + pow(homePosition.y - position.y, 2) > 192)) {
			velocity.x *= -1;
		}

		else if (sqrt(pow(targetPosition.x - position.x, 2) + pow(targetPosition.y - position.y, 2) < 200)) {
			behaviorState = 2;
		}

	case 2:

		if (sqrt(pow(targetPosition.x - position.x, 2) + pow(targetPosition.y - position.y, 2) < 32)) {

		}

		else if (sqrt(pow(targetPosition.x - position.x, 2) + pow(targetPosition.y - position.y, 2) > 400)) {
			behaviorState = 3;
		}


	case 3:
		if ( sqrt(pow(homePosition.x - position.x, 2) + pow(homePosition.y - position.y, 2) < 64)) {
			behaviorState = 1;

		}

	}



}

void Enemy::hit(Entity* hitThis) {

}

//items = { new Item("name", HashMap<Integer, Integer>{2:1, 3:2}),
//		new Item("name2", HashMap<Integer, Integer>{2:1, 3 : 2}), }