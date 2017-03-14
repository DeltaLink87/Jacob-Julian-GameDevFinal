#pragma once
#include <map>
#include <SFML/Graphics.hpp>

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	sf::Texture& loadTexture(std::string);

	std::map<std::string, sf::Texture> textures;
};

