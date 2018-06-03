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
	                        std::vector<Entity>& blocks,
	                        bool def = false);
	static void createInternalBlocks(const std::string& roomName,
	                                 const std::vector<sf::Vector2f>& emptyPositions,
	                                 std::vector<Entity>& blocks,
	                                 bool def = false);

public:
	enum class direction { RIGHT, LEFT, UP, DOWN };

	static json rooms;
	static json defaultRooms;
	static json playerData;
	static json defaultPlayerData;
	static json enemiesData;
	static json defaultEnemiesData;
	static std::unordered_map<std::string, sf::Texture> textures;
	static std::unordered_map<std::string, sf::Font> fonts;

	static void load(); //Loads every resource from disk
	static void save();

	static std::vector<Entity> createBlocks(const std::string& roomName, bool def = false);
	static std::vector<Door> createDoors(const std::string&, bool def = false);
	static std::vector<Key> createKeys(const std::string& roomName, bool def = false);
  static std::vector<Portal> createPortals(const std::string& roomName, bool def = false);
	static std::vector<std::unique_ptr<Enemy>> createEnemies(bool def = false);
	static std::unordered_map<std::string, Room> createRooms(bool def = false);

	static json& getRoomJson(const std::string& name, bool def = false);
	static json& getEnemyJson(int id, bool def = false);
	static json& getDoorJson(const std::string& roomName, int id, bool def = false);
	static json& getKeyJson(const std::string& roomName, int doorId, bool def = false);
};
