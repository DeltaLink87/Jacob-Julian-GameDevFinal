#include "Enemy.h"



Enemy::Enemy() : Entity(400, 300, 20, 20) {

}

Enemy::Enemy(sf::Vector2f startingPosition) : Entity(400, 300, 20, 20) {
	position = startingPosition;
	homePosition = startingPosition;
	velocity.x = 70;
	moving = true;
	behaviorState = 1;

}


Enemy::~Enemy() { }



void Enemy::update(float deltaTime) {



	if (moving)
		position.x += velocity.x * deltaTime;

	position.y += velocity.y * deltaTime;

	velocity.y += 50 * deltaTime;

	if (velocity.y > 300)
		velocity.y = 300;

	hitBox.setPosition(position);
}


void Enemy::updateBehavior(float deltaTime, Entity* target, int type) {
	
	switch (behaviorState) {

	case 1:

		if ( sqrt(pow(homePosition.x - position.x, 2) + pow(homePosition.y - position.y, 2)) > 200) {
			if (position.x > homePosition.x) {
				velocity.x = -70;
			}
			else {
				velocity.x = 70;
			}
		}

		else if (sqrt(pow(target->position.x - position.x, 2) + pow(target->position.y - position.y, 2)) < 100.0) {
			behaviorState = 2;
		}
		break;
	case 2:

		if (sqrt(pow(target->position.x - position.x, 2) + pow(target->position.y - position.y, 2)) < 32 && type == 1) {
			//Attack();
			moving = false;
		}

		else if (sqrt(pow(target->position.x - position.x, 2) + pow(target->position.y - position.y, 2)) > 400) {
			behaviorState = 3;
		}

		break;
	case 3:
		if ( sqrt(pow(homePosition.x - position.x, 2) + pow(homePosition.y - position.y, 2)) < 64) {
			behaviorState = 1;
		}
		break;
	case 4:
		if (attackTime < 1) {
			moving = true;
			behaviorState = 2;
		}
		else
			attackTime -= deltaTime;
		break;
	}

	update(deltaTime);

}



void Enemy::hit(Entity* hitThis) {

}

//items = { new Item("name", HashMap<Integer, Integer>{2:1, 3:2}),
//		new Item("name2", HashMap<Integer, Integer>{2:1, 3 : 2}), }