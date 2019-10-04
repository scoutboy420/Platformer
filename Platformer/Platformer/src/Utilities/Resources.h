#pragma once

/**
* @file
* @brief Resources class. It is static (so accessible everywhere) and responsible for storing all data, textures and fonts
*/

/** @cond */
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "JSON/json.hpp"
/** @endcond */
#include "../Entities/Entity.h"
#include "../Entities/Misc/Door.h"
#include "../Entities/Misc/Key.h"
#include "../Entities/Misc/Portal.h"
#include "../Entities/Enemies/Enemy.h"
#include "../Entities/Obstacles/Obstacle.h"

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
	static json defaultRooms;
	static json playerData;
	static json defaultPlayerData;
	static json enemiesData;
	static json defaultEnemiesData;
	static std::unordered_map<std::string, sf::Texture> textures;
	static std::unordered_map<std::string, sf::Font> fonts;

	/**
	 * \brief Loads every resource from disk
	 */
	static void load();
	/**
	 * \brief Saves every resource to disk
	 */
	static void save();

	static std::vector<Entity> createBlocks(const std::string& roomName);
	static std::vector<Door> createDoors(const std::string&);
	static std::vector<Key> createKeys(const std::string& roomName);
	static std::vector<Portal> createPortals(const std::string& roomName);
	static std::vector<std::unique_ptr<Obstacle>> createObstacles(const std::string& roomName);
	static std::vector<std::unique_ptr<Enemy>> createEnemies();
	static std::unordered_map<std::string, Room> createRooms();

	static json& getRoomJson(const std::string& name);
	static json& getEnemyJson(int id);
	static json& getDoorJson(const std::string& roomName, int id);
	static json& getKeyJson(const std::string& roomName, int doorId);
};
