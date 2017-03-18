#include "Actor.h"
#include <cmath>


Actor::Actor(int x, int y, int width, int height) : Entity(x, y, width, height) { }

Actor::~Actor() { 


}

std::vector<Attack*>& Actor::getAttacks() { return newAttacks; }
void Actor::gotAttacks() { newAttacks.clear(); }

std::vector<Sound>& Actor::getSounds() { return newSounds; }
void Actor::gotSounds() { newSounds.clear(); }

void Actor::dealDamage(float damage, bool assassination) {
	curHealth -= std::max((int)damage - inventory.getTotalArmourDefence(), 0);
}
void Actor::HealHealth(float heal) {
	std::cout << "being Healed" << std::endl;
	curHealth += heal;
	if (curHealth > maxHealth)
		curHealth = maxHealth;
}

void Actor::addInventory(Item* newItem) {
	std::cout << newItem->name << std::endl;
	inventory.addToInventory(newItem);
}


/*void Actor::createAttack(Item* weapon) {
	if (weapon == NULL)
		//newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
		newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this, weapon));
	else if (weapon->attackType == 0)
		//newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this));
		newAttacks.push_back(new MeleeAttack(position.x, position.y, 10, 10, dirLooking, this, weapon));
	else
		//newAttacks.push_back(new Projectile(position.x, position.y, 10, 10, sf::Vector2f(200 * cos(dirLooking), 200 * sin(dirLooking)), this));
		newAttacks.push_back(new Projectile(position.x, position.y, 10, 10, sf::Vector2f(200 * cos(dirLooking), 200 * sin(dirLooking)), this, weapon));
}*/

bool Actor::isFacingRight() {
	return facingRight;
}

void Actor::hitWall(sf::Vector2f newPosition, int dir) {
	setPostion(newPosition);

	if (dir == 2) {
		onGround = true;
		if (isJumping) {
			animationTimer = 0;
			isJumping = false;
		}
		if (velocity.y > 10)
			newSounds.push_back(Sound(position.x + hitBox.getSize().x / 2, position.y + hitBox.getSize().y, std::pow(velocity.y, 3) / 50000, 0.5, !isPlayer));
	}

	if (dir == 0 || dir == 2)
		velocity.y = 0;
	else if (dir == 1 || dir == 3)
		velocity.x = 0;
}

void Actor::hitActor(Actor* otherActor) {
	sf::Vector2f middle = (position + otherActor->getPosition() + hitBox.getSize() * 0.5f + otherActor->getHitBox().getSize() * 0.5f) * 0.5f;

	float difX = (hitBox.getPosition().x + hitBox.getSize().x / 2) - (otherActor->getHitBox().getPosition().x + otherActor->getHitBox().getSize().x / 2);
	float difY = (hitBox.getPosition().y + hitBox.getSize().y / 2) - (otherActor->getHitBox().getPosition().y + otherActor->getHitBox().getSize().y / 2);

	if (abs(difX) < abs(difY) && abs(abs(difX) - abs(difY)) > 2) {
		if (difY > 0) {

			otherActor->hitWall(sf::Vector2f(otherActor->getPosition().x, middle.y - otherActor->getHitBox().getSize().y), 0);
			hitWall(sf::Vector2f(position.x, middle.y), 2);
			//std::cout << "bottom" << std::endl;
		}
		else {
			otherActor->hitWall(sf::Vector2f(otherActor->getPosition().x, middle.y), 2);
			hitWall(sf::Vector2f(position.x, middle.y - hitBox.getSize().y), 0);
			//std::cout << "top" << std::endl;
		}
	}

	else if (abs(abs(difX) - abs(difY)) > 2) {
		//std::cout << abs(difX) << "  " << abs(difY) << std::endl;
		if (difX > 0) {
			otherActor->hitWall(sf::Vector2f(middle.x - otherActor->getHitBox().getSize().x, otherActor->getHitBox().getPosition().y), 1);
			hitWall(sf::Vector2f(middle.x, position.y), 3);
			//std::cout << "right" << std::endl;
		}
		else {
			otherActor->hitWall(sf::Vector2f(middle.x, otherActor->getHitBox().getPosition().y), 3);
			hitWall(sf::Vector2f(middle.x - hitBox.getSize().x, position.y), 1);
			//std::cout << "left" << std::endl;
		}
	}
}

Inventory*  Actor::getInventory() { return &inventory; }
int Actor::getMaxHealth() { return maxHealth; }
int Actor::getHealth() { return curHealth; }