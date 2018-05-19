#pragma once
#include "JSON/json.hpp"
#include "SFML/Graphics.hpp"
#include "../Entities/Entity.h"
#include "../Entities/Door.h"
#include "../Entities/Key.h"
#include <unordered_map>

using json = nlohmann::json;

class Resources
{
	static std::vector<sf::Vector2f> getEmptyPositions(const std::string& roomName);
	static void createWalls(const std::string& roomName,
	                        std::vector<sf::Vector2f> emptyPositions,
	                        std::vector<Entity>& blocks);
	static void createInternalBlocks(const std::string& roomName,
	                                 const std::vector<sf::Vector2f>& emptyPositions,
	                                 std::vector<Entity>& blocks);

public:
	enum class direction { RIGHT, LEFT, UP, DOWN };

	static json rooms;
	static json playerData;
	static std::unordered_map<std::string, sf::Texture> textures;
	static std::unordered_map<std::string, sf::Font> fonts;

	static void load(); //Loads every resource from disk
	static void save();
	static std::vector<Entity> createBlocks(int roomId);
	static std::vector<Door> createDoors(int roomId, std::vector<bool> openedDoors);
	static std::vector<Key> createKeys(int roomId, std::vector<bool> openedDoors);

	static int countRooms();
	static int getRoomId(const std::string& roomName);
	static int highestDoorId();
};
