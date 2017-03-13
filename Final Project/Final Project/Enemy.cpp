#include "Enemy.h"



Enemy::Enemy() : Actor(400, 300, 20, 20) {

}

Enemy::Enemy(sf::Vector2f startingPosition, ItemManager* itemManager) : Actor(400, 300, 20, 20) {
	position = startingPosition;
	homePosition = startingPosition;
	velocity.x = 70;
	moving = true;
	behaviorState = 1;
	maxHealth = curHealth = 10;

	addInventory(itemManager->getItem("Wood"));
	addInventory(itemManager->getItem("Blade"));
	//addInventory(itemManager->getItem("Herb"));
}


Enemy::~Enemy() { }



void Enemy::update(float deltaTime) {

	if (curHealth <= 0) {
		remove();
		return;
	}

	if (behaviorState == 1) {
		if (pow(homePosition.x - position.x, 2) + pow(homePosition.y - position.y, 2) > pow(200, 2)) {
			if (position.x > homePosition.x + 200) {
				velocity.x = -70;
			}
			else if (position.x < homePosition.x - 200) {
				velocity.x = 70;
			}
		}
		//std::cout << "patrol" << std::endl;
	}
	else if (behaviorState == 2) {
		if (position.x > targetLocation.x) {
			velocity.x = -70;
		}
		else if (position.x < targetLocation.x) {
			velocity.x = 70;
		}

		//if (pow(targetLocation.x - position.x, 2) + pow(targetLocation.y - position.y, 2) < pow(32, 2)) {
		if (abs(targetLocation.x - position.x) < 32){
			behaviorState = 4;
		}
		//std::cout << "investigate" << std::endl;
	}
	else if (behaviorState == 3) {
		if (position.x > targetLocation.x) {
			velocity.x = -70;
		}
		else if (position.x < targetLocation.x) {
			velocity.x = 70;
		}

		if (pow(targetLocation.x - position.x, 2) + pow(targetLocation.y - position.y, 2) < pow(32, 2)) {
			//making either a melee attack or projectile attack
			if (attackTimer <= 0) {
				attackTimer = 0.5;
				newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
				//newAttacks.push_back(new Projectile(position.x, position.y, 10, 10, sf::Vector2f(200 * cos(dirLooking), 200 * sin(dirLooking)), this));
			}
			moving = false;
		}
		else moving = true;

		//if (pow(targetLocation.x - position.x, 2) + pow(targetLocation.y - position.y, 2) > pow(400, 2)) {
		/*if (abs(targetLocation.x - position.x) < 32) {
			behaviorState = 4;
		}*/
		//std::cout << "chase" << std::endl;
	}
	else if (behaviorState == 4) {
		if (position.x > homePosition.x) {
			velocity.x = -70;
		}
		else if (position.x < homePosition.x) {
			velocity.x = 70;
		}

		if (pow(homePosition.x - position.x, 2) + pow(homePosition.y - position.y, 2) < pow(64, 2)) {
			behaviorState = 1;
		}
		moving = true;
		//std::cout << "return" << std::endl;
	}

	if (moving)
		position.x += velocity.x * deltaTime;

	position.y += velocity.y * deltaTime;

	velocity.y += 50 * deltaTime;

	if (velocity.y > 100)
		velocity.y = 100;

	if (behaviorState == 3) {
		if (position.x - targetLocation.x > 0)
			dirLooking = 2 * acos(0);
		else if (position.x - targetLocation.x < 0)
			dirLooking = 0;
	}
	else {
		if (velocity.x < 0)
			dirLooking = 2 * acos(0);
		else if (velocity.x > 0)
			dirLooking = 0;
	}

	attackTimer -= deltaTime;
	/*timer++;
	if (timer % 5 == 0)
		std::cout << position.x << "," << position.y << "," << velocity.x << "," << velocity.y << std::endl;*/
	hitBox.setPosition(position);
}

void Enemy::doesHear(Sound* checkSound) {
	sf::Vector2f soundLocation = checkSound->getPosition();
	if (behaviorState != 3 && pow(checkSound->getLoudness(), 2) > pow(position.x - soundLocation.x, 2) + pow(position.y - soundLocation.y, 2)) {
		targetLocation = soundLocation;
		behaviorState = 2;
	}
}

void Enemy::doesSee(Actor* checkActor) {
	sf::Vector2f actorLocation = checkActor->getPosition();

	//checking if the actor is within the enemy's range of sight
	if (pow(200, 2) > pow(position.x - actorLocation.x, 2) + pow(position.y - actorLocation.y, 2)) {
		//calculating angle from enemy to actor
		float dirToActor = atan((actorLocation.y - position.y) / (actorLocation.x - position.x));
		if (actorLocation.x - position.x < 0)
			dirToActor += 2 * acos(0);
		//checking if the actor is in the direction the enemy is looking
		if (abs(dirToActor - dirLooking) < acos(0) / 2) {
			//changes behaviour to chase if sees actor and makes it's location the target location to go to
			targetLocation = checkActor->getPosition();
			behaviorState = 3;
		}
		else if (behaviorState == 3) {	//changing behaviour to investigate if loses sight of actor
			behaviorState = 2;
		}
	}
	else if (behaviorState == 3) {
		behaviorState = 2;
	}
}

void Enemy::hitWall(sf::Vector2f newPosition, int dir) {
	setPostion(newPosition);

	if (dir == 0 || dir == 2)
		velocity.y = 0;
	else if (dir == 1 || dir == 3)
		velocity.x = -velocity.x;
}

void Enemy::overEdge() {
	velocity.x = -velocity.x;
}

Loot* Enemy::lootDrop() { return new Loot(position.x, position.y, 10, 10, inventory.dropRandom()); }

//items = { new Item("name", HashMap<Integer, Integer>{2:1, 3:2}),
