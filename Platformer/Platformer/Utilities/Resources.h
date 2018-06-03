#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "JSON/json.hpp"
#include "../Entities/Entity.h"
#include "../Entities/Door.h"
#include "../Entities/Key.h"
#include "../Entities/Portal.h"
#include "../Entities/Enemy.h"

class Room;

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
	static json enemiesData;
	static std::unordered_map<std::string, sf::Texture> textures;
	static std::unordered_map<std::string, sf::Font> fonts;

	static void load(); //Loads every resource from disk
	static void save();
	static std::vector<Entity> createBlocks(const std::string& roomName);
	static std::vector<Door> createDoors(const std::string& roomName);
	static std::vector<Key> createKeys(const std::string& roomName);
	static std::vector<Portal> createPortals(const std::string& roomName);
	static std::vector<std::unique_ptr<Enemy>> createEnemies();
	static std::unordered_map<std::string, Room> createRooms();

	static json& getRoomJson(const std::string& name);
};
