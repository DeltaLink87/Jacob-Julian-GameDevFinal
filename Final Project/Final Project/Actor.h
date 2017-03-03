#pragma once

#include "Entity.h"
#include "Sound.h"
#include "UseableItem.h"
#include "Equipment.h"
#include "Item.h"

//#include "Attack.h"
class Attack;

class Actor : public Entity {
public:
	Actor(int, int, int, int);
	~Actor();


	void addInventory(Item*);


	std::vector<Sound>& getSounds();
	std::vector<Sound> newSounds;
	float stepSoundTimer = 0;

	std::vector<Attack*>& getAttacks();
	std::vector<Attack*> newAttacks;
	float attackTimer = 0;
	bool attack = false;


	std::map<std::string, Item*> inventory;

};

