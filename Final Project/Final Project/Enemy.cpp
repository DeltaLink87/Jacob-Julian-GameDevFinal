#include "Enemy.h"



Enemy::Enemy() : Actor(400, 300, 20, 20) {

}

Enemy::Enemy(sf::Vector2f startingPosition) : Actor(400, 300, 20, 20) {
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

	if (velocity.y > 100)
		velocity.y = 100;

	/*timer++;
	if (timer % 5 == 0)
		std::cout << position.x << "," << position.y << "," << velocity.x << "," << velocity.y << std::endl;*/
	hitBox.setPosition(position);
}


void Enemy::updateBehavior(float deltaTime, Entity* target, int type) {
	
	switch (behaviorState) {

	case 1:

		if ( sqrt(pow(homePosition.x - position.x, 2) + pow(homePosition.y - position.y, 2)) > 200) {
			if (position.x > homePosition.x + 200) {
				velocity.x = -70;
			}
			else if (position.x < homePosition.x - 200) {
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
