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

		description = "Short thrusting weapon. Stabbing an unaware enemy is effective. NL Damage: 1 NL Can be used to Assassinate.";
		type = "Weapon/Material";

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
		description = "Standard short sword, good for dealing with opponents head on. NL Damage: 3";
		type = "Weapon/Material";

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

		description = "Long thrusting weapon, favored amungst cowards. NL Damage: 2";
		type = "Weapon";

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

		description = "The Dagger's big brother. NL Damage: 3 NL Can be used to Assassinate.";
		type = "Weapon/Material";

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

		attack = 7;
		canAssassinate = true;


		recipe.insert(std::pair<std::string, int>("Rondel", 1));
		recipe.insert(std::pair<std::string, int>("Steel", 2));

		description = "It's bigger, faster, and stronger too. It's the best member of the Dagger crew. NL Damage: 6 NL Can be used to Assassinate.";
		type = "Weapon/Material";


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
		description = "A longer, stronger sword. NL Damage: 5";
		type = "Weapon/Material";


		presetItemDimX = 34;
		presetItemDimY = 16;
		dimPreset = true;


		isWeapon = true;

		attackType = 1;
	}
	else if (index == 7) {
		name = n;
		
		attack = 7;

		//Because weapons can't have a greater quantity per slot than 1, 
		//assuming having the recipe listed as two individual long swords 
		//will be preferable.
		recipe.insert(std::pair<std::string, int>("LongSword", 2));
		description = "A thick study sword used by veterans. NL Damage: 7";
		type = "Weapon/Material";



		presetItemDimX = 34;
		presetItemDimY = 20;
		dimPreset = true;

		isWeapon = true;

		attackType = 1;


	}

	else if (index == 8) {
		name = n;

		attack = 10;


		recipe.insert(std::pair<std::string, int>("BroadSword", 1));
		recipe.insert(std::pair<std::string, int>("Steel", 2));
		description = "A massive piece of steel used by Elite Knights. NL Damage: 10";
		type = "Weapon/Material";


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
		type = "Weapon";
		isWeapon = true;


		description = "A Legendary sword resulting from a Romeo and Juliette romance between the strongest Sword and Dagger. NL Damage: 20";

		presetItemDimX = 46;
		presetItemDimY = 20;
		dimPreset = true;

		attackType = 1;


	}
	/*
	else if (index == 10) {
		name = n;

		attack = 2;


		recipe.insert(std::pair<std::string, int>("Wood", 1));
		recipe.insert(std::pair<std::string, int>("String", 2));
		isWeapon = true;

		description = "Excellent at flinging pointed sticks at people you don't like. NL Damage: 3 NL Requires Arrows to use.";
		type = "Weapon";

		presetItemDimX = 24;
		presetItemDimY = 11;
		dimPreset = true;


		attackType = 2;

	}
	*/
	else if (index == 11) {
		name = n;
		defence = 1;
		armourType = 1;

		description = "Reliable leather armor, grants immunity to scrapes and papercuts. NL Defence: 1";
		type = "Armour";

		recipe.insert(std::pair<std::string, int>("Leather", 2));
		recipe.insert(std::pair<std::string, int>("String", 1));

	}
	else if (index == 12) {
		name = n;
		defence = 1;
		armourType = 2;

		description = "Reliable leather armor, grants immunity to scrapes and papercuts. NL Defence: 1";
		type = "Armour";

		recipe.insert(std::pair<std::string, int>("Leather", 2));
		recipe.insert(std::pair<std::string, int>("String", 1));
	}
	else if (index == 13) {
		name = n;
		defence = 1;
		armourType = 3;

		description = "Reliable leather armor, grants immunity to scrapes and papercuts. NL Defence: 1";
		type = "Armour";

		recipe.insert(std::pair<std::string, int>("Leather", 2));
		recipe.insert(std::pair<std::string, int>("String", 1));
	}
	else if (index == 14) {
		name = n;
		defence = 1;
		armourType = 4;

		description = "Reliable leather armor, grants immunity to scrapes and papercuts. NL Defence: 1";
		type = "Armour";

		recipe.insert(std::pair<std::string, int>("Leather", 2));
		recipe.insert(std::pair<std::string, int>("String", 1));
	}
	else if (index == 15) {
		name = n;
		defence = 1;
		armourType = 1;

		description = "Reliable leather armor, grants immunity to scrapes and papercuts. NL Defence: 1";
		type = "Armour";

		recipe.insert(std::pair<std::string, int>("Leather", 2));
		recipe.insert(std::pair<std::string, int>("String", 1));
	}
	else if (index == 16) {
		name = n;
		defence = 3;
		armourType = 2;

		description = "Very strong and sturdy armor. Worn by knights and nobels. NL Defence: 3";
		type = "Armour";

		recipe.insert(std::pair<std::string, int>("Iron", 4));
	}
	else if (index == 17) {
		name = n;
		defence = 3;
		armourType = 3;

		description = "Very strong and sturdy armor. Worn by knights and nobels. NL Defence: 3";
		type = "Armour";

		recipe.insert(std::pair<std::string, int>("Iron", 4));
	}

	else if (index == 18) {
		name = n;
		defence = 3;
		armourType = 4;

		description = "Very strong and sturdy armor. Worn by knights and nobels. NL Defence: 3";
		type = "Armour";

		recipe.insert(std::pair<std::string, int>("Iron", 4));
	}

}
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
11: LeatherHelm
12: LeatherTunic
13: LeatherPants
14: LeatherBoots
15: IronHelm
16: IronBreastPlate
17: IronLegGuards
18: IronBoots
*/

Item* Equipment::getCopy() {
	return new Equipment(*this);
}
