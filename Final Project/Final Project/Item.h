#pragma once

#include "Entity.h"


class Item {
public:
	Item(std::string, int);
	Item(int);
	Item(Item*);
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

	int quantity = 0;

	sf::Image image;

	std::string name;
	
	sf::Sprite smallIcon;
	sf::Sprite menuIcon;
	sf::Sprite menuDescription;


	sf::Texture smallIconTexture;
	sf::Texture menuIconTexture;
	sf::Texture menuDescriptionTexture;







};

