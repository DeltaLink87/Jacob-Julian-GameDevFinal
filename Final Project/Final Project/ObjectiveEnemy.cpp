#include "ObjectiveEnemy.h"



ObjectiveEnemy::ObjectiveEnemy(sf::Vector2f startingPosition, ItemManager* itemManager, MovementMap* map) : Enemy(startingPosition, itemManager, map) {
	flagPosDif = sf::Vector2f(0, -20);
}


ObjectiveEnemy::~ObjectiveEnemy() { }


void ObjectiveEnemy::remove() {
	Entity::remove();
	complete = true;
}

void ObjectiveEnemy::reset(){}