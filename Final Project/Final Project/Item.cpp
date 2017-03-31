#include "Item.h"


Item::Item(std::string string, int identifier) {
	this->name = string;
	this->id = identifier;

	setTextures(string);

}

Item::Item(int identifier) {
	this->id = identifier;

}

/*tem::Item(Item& oldItem) {
	name = oldItem.name;
	id = oldItem.id;
	recipe = oldItem.recipe;
	quantity = oldItem.quantity;

	attack = oldItem.attack;
	attackType = oldItem.attackType;
	defence = oldItem.defence;
	armourType = oldItem.armourType;

	smallIconTexture = oldItem.smallIconTexture;
	smallIcon.setTexture(smallIconTexture);

	menuIconTexture = oldItem.menuIconTexture;
	menuIcon.setTexture(menuIconTexture);

	menuDescriptionTexture = oldItem.menuDescriptionTexture;
	menuDescription.setTexture(menuDescriptionTexture);
}*/


void Item::setTextureWithMask(sf::Texture* texture, std::string file) {
	this->image.loadFromFile(file);
	this->image.createMaskFromColor(sf::Color::White);
	texture->loadFromImage(image);

}


void Item::setTextures(std::string string) {

	//smallIcon.setScale(sf::Vector2f(50, 50));
	//menuIcon.setScale(sf::Vector2f(2.6, 1.4));
	//menuDescription.setScale(sf::Vector2f(265, 300));

	//image.loadFromFile("Assets/Textures/" + string + ".png");
	setTextureWithMask(&smallIconTexture, "Assets/Textures/Items/" + string + "Icon.png");
	setTextureWithMask(&menuIconTexture, "Assets/Textures/Items/" + string + "Icon.png");
	//setTextureWithMask(&menuDescriptionTexture, "Assets/Textures/Items/" + string + "Description.png");

	smallIcon.setTexture(smallIconTexture);
	menuIcon.setTexture(menuIconTexture);
	menuDescription.setTexture(menuDescriptionTexture);

	smallIcon.setScale(sf::Vector2f(75.0 / smallIcon.getTexture()->getSize().x, 75.0 / smallIcon.getTexture()->getSize().y));
	menuIcon.setScale(sf::Vector2f(1, 1));
	//menuIcon.setScale(sf::Vector2f(100.0 / menuIcon.getTexture()->getSize().x, 75.0 / menuIcon.getTexture()->getSize().y));
	//menuDescription.setScale(sf::Vector2f(280.0 / menuDescription.getTexture()->getSize().x, 350.0 / menuDescription.getTexture()->getSize().y));

	//std::cout << id << std::endl;
}


Item::~Item() {


}

Item* Item::getCopy() {
	return new Item(*this);
}

bool Item::useItem(Entity* usedBy) { 
	//usedBy->HealHealth(amountToHeal);
	//durability -= durLossPerUse;
	//return (durability <= 0);
	return false;
}

/*
Will make:
4x material icons
1x equipment icon
1x useable item icon
1x equipment menuicon
1x useable menuicon
1x equip desc
1x use desc

player inventory UI

*/