#pragma once

#include "Entity.h"
#include "Sound.h"
#include "UseableItem.h"
#include "Equipment.h"
#include "Item.h"
#include "Loot.h"
#include "Inventory.h"

//#include "Attack.h"
class Attack;

class Actor : public Entity {
public:
	Actor(int, int, int, int);
	~Actor();

	void hitWall(sf::Vector2f, int);

	void addInventory(Item*);


	std::vector<Sound>& getSounds();
	void gotSounds();
	std::vector<Attack*> newAttacks;
	void gotAttacks();

	int getMaxHealth();
	int getHealth();

	void dealDamage(float);

	bool isFacingRight();



protected:
	std::vector<Sound> newSounds;
	float stepSoundTimer = 0;
	
	//void createAttack(Item*);
	std::vector<Attack*>& getAttacks();
	float attackTimer = 0;
	bool attack = false;
  
	Inventory inventory;
	int curItemSelected = 0;

	bool climbing = false;
	bool facingRight;
	bool onGround = true;

	float dirLooking = 0;

	int maxHealth, curHealth;
	int maxStamina, curStamina;
	int maxMagic, curMagic;
	float attackStat, defenceStat, speedStat;
};

