#pragma once

#include "Entity.h"
#include "Sound.h"
#include "UseableItem.h"
#include "Equipment.h"
#include "Item.h"
#include "Loot.h"

//#include "Attack.h"
class Attack;

class Actor : public Entity {
public:
	Actor(int, int, int, int);
	~Actor();


	void addInventory(Item*);


	std::vector<Sound>& getSounds();
	void gotSounds();
	std::vector<Attack*> newAttacks;
	void gotAttacks();

	void dealDamage(float);

protected:
	std::vector<Sound> newSounds;
	float stepSoundTimer = 0;
	
	std::vector<Attack*>& getAttacks();
	float attackTimer = 0;
	bool attack = false;
  
	std::map<std::string, Item*> inventory;

	bool climbing = false;

	float dirLooking = 0;

	int maxHealth, curHealth;
	int maxStamina, curStamina;
	int maxMagic, curMagic;
	float attackStat, defenceStat, speedStat;
};

