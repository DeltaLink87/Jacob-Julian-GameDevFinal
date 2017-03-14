#include "AssetManager.h"


AssetManager::AssetManager() { }

AssetManager::~AssetManager() { }

sf::Texture& AssetManager::loadTexture(std::string texturePath) {
	if (textures.count(texturePath) != 0)
		return textures.at(texturePath);

	sf::Texture newTexture;
	newTexture.loadFromFile("Assets/Textures/" + texturePath + ".png");
	textures.insert(std::pair<std::string, sf::Texture>(texturePath, newTexture));
	return textures.at(texturePath);
}