#include "Attack.h"

Attack::Attack(int x, int y, int width, int height, Actor* newSource) : Entity(x, y, width, height) {
	source = newSource;
	//sprite.setFillColor(sf::Color::Blue);
	textureName = "Attacks/Attack";
}

Attack::~Attack() { }

void Attack::hitTile(Tile* hitThis) {
	if (hitThis->isSolid()) {
		if (this->melee)
			collidedWithTile = true;
		else
			remove();
	}
}

void Attack::rotation(float dir) {

	//this->visualRepresentation.setPosition(this->visualRepresentation.getPosition() - sf::Vector2f(this->visualRepresentation.getScale().x /2,this->visualRepresentation.getScale().y / 2));
	//std::cout << dir << std::endl;
	this->visualRepresentation.setRotation(dir * 57.2957795);
	
	//this->visualRepresentation.setPosition(this->visualRepresentation.getPosition() + sf::Vector2f(this->visualRepresentation.getScale().x / 2, this->visualRepresentation.getScale().y / 2));
}

void Attack::hitActor(Actor* hitThis) {
	//std::cout << "hit" << std::endl;
	bool exitBool = false;
	if (this->piercing || this->melee) {
		if (!this->attacked.empty()) {
			for (std::vector<Actor*>::iterator i = this->attacked.begin(); i != this->attacked.end(); i++) {
				if (hitThis == *i) {
					exitBool = true;
				}
			}
		}
	}
	if (exitBool) {
		
		return;
		std::cout << "Why AM I here!?!" << std::endl;
	}


	if (hitThis != source) {
		hitThis->dealDamage(damage);
		attacked.push_back(hitThis);
		//std::cout << hitThis->curHealth << std::endl;
		if(!this->piercing && !this->melee)
			remove();
	}
}