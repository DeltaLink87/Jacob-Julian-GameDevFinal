#pragma once

#include "Updatable.h"
#include "Renderable.h"

class Entity : public Updatable, public Renderable {
public:
	Entity(int, int, int, int);
	~Entity();

	//checks if this entity's hitbox intersects with another rectangle
	bool intersects(sf::RectangleShape);

	void setPostion(sf::Vector2f);	
	sf::Vector2f& getPosition();
	sf::RectangleShape& getHitBox();
	/*
	Sets position of the player and stops velocity in the direction of the wall hit
	(vector2f position, int direction)
	0:Up	1:Left	2:Down	3:Right
	*/
	virtual void hitWall(sf::Vector2f, int);
	
	

	bool nextToClimbable = false;
	
	//std::map<std::string, int> stats;

	void remove();
	bool isRemoved();
protected:
	sf::RectangleShape hitBox;
	sf::Vector2f velocity;

	
private:
	bool removed = false;
};

