#include "ObjectiveEnemy.h"



ObjectiveEnemy::ObjectiveEnemy(sf::Vector2f startingPosition, ItemManager* itemManager) : Enemy(startingPosition, itemManager) {
	flagPosDif = sf::Vector2f(0, -20);
}


ObjectiveEnemy::~ObjectiveEnemy() { }


void ObjectiveEnemy::remove() {
	Entity::remove();
	complete = true;
}

void ObjectiveEnemy::reset(){}