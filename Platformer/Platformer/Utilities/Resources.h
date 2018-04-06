#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include "Map.h"

class Resources
{
public:
	static Map map;
	static std::unordered_map<std::string, sf::Texture> textureMap;

	/**
	* \brief Loads map, rooms structure and textures from disk
	*/
	static void load();
};
