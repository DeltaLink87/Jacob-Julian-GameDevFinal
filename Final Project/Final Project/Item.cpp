
#include "Item.h"

Item::Item(std::string string, int identifier) {
	this->name = string;
	this->id = identifier;

	setTextures(string);

}

Item::Item(int identifier) {
	this->id = identifier;

}


void Item::setTextureWithMask(sf::Texture* texture, std::string file) {
	this->image.loadFromFile(file);
	this->image.createMaskFromColor(sf::Color::Black);
	texture->loadFromImage(image);

}


void Item::setTextures(std::string string) {
	
	//smallIcon.setScale(sf::Vector2f(50, 50));
	menuIcon.setScale(sf::Vector2f(2.6, 1.4));
	//menuDescription.setScale(sf::Vector2f(265, 300));
	
	image.loadFromFile("Assets/tempIMG.png");
	setTextureWithMask(&smallIconTexture, "Assets/tempIMG.png");
	setTextureWithMask(&menuIconTexture, "Assets/tempIMG.png");
	setTextureWithMask(&menuDescriptionTexture, "Assets/tempIMG.png");


	smallIcon.setTexture(smallIconTexture);
	menuIcon.setTexture(menuIconTexture);
	menuDescription.setTexture(menuDescriptionTexture);
	


	std::cout << "TESTTTT" << std::endl;
}


Item::~Item() {


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





