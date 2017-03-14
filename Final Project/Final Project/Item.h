#pragma once

#include <string>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <iostream>

class Item
{
public:
	Item(std::string, int);
	Item(int);
	~Item();

	//string to be used in finding filename
	void setTextures(std::string);

	void setTextureWithMask(sf::Texture*, std::string);

	/*
	key = string(name)
	value = int(quantity required)
	*/
	std::map<std::string, int> recipe;

	/*
	To distinguish between a basic item to be used as a material, and the further defined Equipment/UseableItem classes
	1 = material
	2 = Equipment
	3 = UseableItem
	*/
	int id;

	//amount of damage this item will do
	int attack = 1;
	/*type of attack this items makes
	1: melee attack
	2: projectile attack*/
	int attackType = 0;
	/*type of armour this item is
	0: not armour
	1: helmet
	2: chestplate
	3: leggings
	4: boots*/
	int armourType = 0;
	//amount of damage this item will block if used as armour
	int defence = 0;

	int quantity = 1;

	sf::Image image;

	std::string name;

	sf::Sprite smallIcon;
	sf::Sprite menuIcon;
	sf::Sprite menuDescription;


	sf::Texture smallIconTexture;
	sf::Texture menuIconTexture;
	sf::Texture menuDescriptionTexture;
};

