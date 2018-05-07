#pragma once
#include "JSON/json.hpp"
#include "SFML/Graphics.hpp"
#include "../Entities/Entity.h"
#include <unordered_map>

using json = nlohmann::json;

class Resources
{
public:
	enum class direction { RIGHT, LEFT, UP, DOWN };

	static json rooms_;
	static json playerData_;
	static std::unordered_map<std::string, sf::Texture> textures_;

	static void load(); //Loads every resource from disk
	static void save();
	static std::vector<Entity> createEntities(int roomId);

	static int getRoomId(std::string roomName);
};
