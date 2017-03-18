#pragma once
#include "Equipment.h"


/*Item Index Reference:
1:  Dagger
2:  Sword
3:  Spear
4:  Rondel (upgraded dagger)
5:  SinnersScalpel (upgraded Rondel)
6:  LongSword (upgraded sword)
7:  BroadSword (upgraded LongSword)
8:  GreatSword (upgraded BroadSword)
9:  MasterfulSword (upgraded GreatSword)
10: Bow
13: BreastPlate
*/
Equipment::Equipment(std::string n, int index) : Item(n, 2) {

	if (index == 1) {
		name = n;
		agility = 1;
		strength = 4;
		attack = 1;
		canAssassinate = true;
		recipe.insert(std::pair<std::string, int>("Blade", 1));
		recipe.insert(std::pair<std::string, int>("Wood", 1));
		isWeapon = true;

		presetItemDimX = 26;
		presetItemDimY = 12;
		dimPreset = true;

		attackType = 0;
	}
	else if (index == 2) {
		name = n;

		attack = 3;
		canAssassinate = false;

		recipe.insert(std::pair<std::string, int>("Blade", 2));
		recipe.insert(std::pair<std::string, int>("Wood", 2));

		presetItemDimX = 29;
		presetItemDimY = 14;
		dimPreset = true;

		isWeapon = true;

		attackType = 1;
	}
	else if (index == 3) {
		name = n;

		attack = 2;
		canAssassinate = false;
		
		recipe.insert(std::pair<std::string, int>("Blade", 1));
		recipe.insert(std::pair<std::string, int>("Wood", 4));
		

		presetItemDimX = 40;
		presetItemDimY = 10;
		dimPreset = true;

		isWeapon = true;

		attackType = 0;

	}
	else if (index == 4) {
		name = n;

		attack = 3;
		canAssassinate = true;


		recipe.insert(std::pair<std::string, int>("Dagger", 1));
		recipe.insert(std::pair<std::string, int>("Iron", 1));


		presetItemDimX = 32;
		presetItemDimY = 12;
		dimPreset = true;

		isWeapon = true;

		attackType = 0;

	}

	else if (index == 5) {
		name = n;

		attack = 5;
		canAssassinate = true;


		recipe.insert(std::pair<std::string, int>("Rondel", 1));
		recipe.insert(std::pair<std::string, int>("Steel", 2));


		presetItemDimX = 45;
		presetItemDimY = 21;
		dimPreset = true;


		isWeapon = true;

		attackType = 0;

	}
	else if (index == 6) {
		name = n;

		attack = 5;
		canAssassinate = false;


		recipe.insert(std::pair<std::string, int>("Sword", 1));
		recipe.insert(std::pair<std::string, int>("Iron", 1));


		presetItemDimX = 34;
		presetItemDimY = 16;
		dimPreset = true;


		isWeapon = true;

		attackType = 1;
	}
	else if (index == 7) {
		name = n;
		
		attack = 8;

		//Because weapons can't have a greater quantity per slot than 1, 
		//assuming having the recipe listed as two individual long swords 
		//will be preferable.
		recipe.insert(std::pair<std::string, int>("LongSword", 1));
		recipe.insert(std::pair<std::string, int>("LongSword", 1));



		presetItemDimX = 34;
		presetItemDimY = 20;
		dimPreset = true;

		isWeapon = true;

		attackType = 1;


	}

	else if (index == 8) {
		name = n;

		attack = 11;


		recipe.insert(std::pair<std::string, int>("BroadSword", 1));
		recipe.insert(std::pair<std::string, int>("Steel", 2));


		presetItemDimX = 38;
		presetItemDimY = 17;
		dimPreset = true;


		isWeapon = true;

		attackType = 1;
		
	}
	//Probably remove tile collision for this one and the other giant weapons at some point
	else if (index == 9) {
		name = n;

		attack = 20;


		recipe.insert(std::pair<std::string, int>("GreatSword", 1));
		recipe.insert(std::pair<std::string, int>("SinnersScalpel", 1));
		isWeapon = true;


		presetItemDimX = 46;
		presetItemDimY = 20;
		dimPreset = true;

		attackType = 1;


	}

	else if (index == 10) {
		name = n;

		attack = 20;


		recipe.insert(std::pair<std::string, int>("Wood", 1));
		recipe.insert(std::pair<std::string, int>("String", 2));
		isWeapon = true;


		presetItemDimX = 24;
		presetItemDimY = 11;
		dimPreset = true;


		attackType = 2;

	}


	else if (index == 13) {
		name = n;
		defence = 2;
		armourType = 2;

		recipe.insert(std::pair<std::string, int>("Iron", 4));
	}

}

Item* Equipment::getCopy() {
	return new Equipment(*this);
}
