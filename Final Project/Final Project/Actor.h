#pragma once

#include "Entity.h"
#include "Sound.h"
//#include "UseableItem.h"
//#include "Equipment.h"
//#include "Loot.h"
#include "Inventory.h"

//#include "Item.h"
//class Item;

//#include "Attack.h"
class Attack;

class Actor : public Entity {
public:
	Actor(int, int, int, int);
	~Actor();

	void hitWall(sf::Vector2f, int);
	void hitActor(Actor*);

	void addInventory(Item*);
	Inventory* getInventory();

	std::vector<Sound>& getSounds();
	void gotSounds();
	std::vector<Attack*> newAttacks;
	void gotAttacks();

	int getMaxHealth();
	int getHealth();

	void dealDamage(float, bool);
	void HealHealth(float);

	bool isFacingRight();

	float dirLooking = 0;

	float animationTimer;
	bool isJumping = false;
	bool isIdle = true;;
	bool isRunning = false;
	bool isClimbing = false;
	bool isAttacking = false;

protected:
	std::vector<Sound> newSounds;
	float stepSoundTimer = 0;

	int damageFlicker = 0;
	
	//void createAttack(Item*);
	std::vector<Attack*>& getAttacks();
	float attackTimer = 0;
	bool attack = false;
  
	Inventory inventory;
	int curItemSelected = 0;

	bool climbing = false;
	bool facingRight;
	bool onGround = true;

	//float dirLooking = 0;

	int maxHealth, curHealth;
	int maxStamina, curStamina;
	int maxMagic, curMagic;
	float attackStat, defenceStat, speedStat;


};

