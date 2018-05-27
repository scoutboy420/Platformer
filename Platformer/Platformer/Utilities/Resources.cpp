#include "Resources.h"
#include <fstream>
#include "../Entities/Walker.h"
#include "Room.h"

json Resources::rooms;
json Resources::playerData;
json Resources::enemiesData;
std::unordered_map<std::string, sf::Texture> Resources::textures;
std::unordered_map<std::string, sf::Font> Resources::fonts;

/* Sebastian Pietras */
void Resources::load()
{
	std::ifstream i;

	i.open("Data/JSON/rooms.json");
	i >> rooms;
	i.close();
	i.clear();

	i.open("Data/JSON/player.json");
	i >> playerData;
	i.close();
	i.clear();

	i.open("Data/JSON/enemies.json");
	i >> enemiesData;
	i.close();
	i.clear();

	textures["player"].loadFromFile("Data/Textures/player.png");
	textures["block"].loadFromFile("Data/Textures/block.png");
	textures["enemy1"].loadFromFile("Data/Textures/enemy1.png");

	/*textures: Bernard Lesiewicz*/
	textures["door_rd"].loadFromFile("Data/Textures/door_rd.png");
	textures["door_gr"].loadFromFile("Data/Textures/door_gr.png");
	textures["door_bl"].loadFromFile("Data/Textures/door_bl.png");
	textures["door_or"].loadFromFile("Data/Textures/door_or.png");
	textures["door_mg"].loadFromFile("Data/Textures/door_mg.png");
	textures["door_yl"].loadFromFile("Data/Textures/door_yl.png");
	textures["door_wh"].loadFromFile("Data/Textures/door_wh.png");
	textures["door_gy"].loadFromFile("Data/Textures/door_gy.png");
	textures["door_bk"].loadFromFile("Data/Textures/door_bk.png");

	textures["key_rd"].loadFromFile("Data/Textures/key_rd.png");
	textures["key_gr"].loadFromFile("Data/Textures/key_gr.png");
	textures["key_bl"].loadFromFile("Data/Textures/key_bl.png");
	textures["key_or"].loadFromFile("Data/Textures/key_or.png");
	textures["key_mg"].loadFromFile("Data/Textures/key_mg.png");
	textures["key_yl"].loadFromFile("Data/Textures/key_yl.png");
	textures["key_wh"].loadFromFile("Data/Textures/key_wh.png");
	textures["key_gy"].loadFromFile("Data/Textures/key_gy.png");
	textures["key_bk"].loadFromFile("Data/Textures/key_bk.png");

	fonts["vcr"].loadFromFile("Data/Fonts/vcr.ttf");
}

/* Sebastian Pietras */
void Resources::save()
{
	std::ofstream o;

	o.open("Data/JSON/rooms.json", std::ofstream::out | std::ofstream::trunc);
	o << std::setw(4) << rooms;
	o.close();
	o.clear();

	o.open("Data/JSON/player.json", std::ofstream::out | std::ofstream::trunc);
	o << std::setw(4) << playerData;
	o.close();
	o.clear();

	o.open("Data/JSON/player.json", std::ofstream::out | std::ofstream::trunc);
	o << std::setw(4) << playerData;
	o.close();
	o.clear();
}

/* Sebastian Pietras */
std::vector<sf::Vector2f> Resources::getEmptyPositions(const std::string& roomName)
{
	std::vector<sf::Vector2f> emptyPos;

	for(const auto& entrances : json(getRoomJson(roomName).at("entrances")))
	{
		const auto entranceWidth = entrances.at("width").get<int>(), entranceHeight = entrances.at("height").get<int>();
		const auto entrancePos = sf::Vector2f(entrances.at("x").get<float>(), entrances.at("y").get<float>());

		for(auto i = 0; i < entranceWidth; i++)
		{
			for(auto j = 0; j < entranceHeight; j++)
			{
				emptyPos.push_back(sf::Vector2f(entrancePos.x + i * 50.0f, entrancePos.y + j * 50.0f));
			}
		}
	}

	return emptyPos;
}

/* Sebastian Pietras */
void Resources::createWalls(const std::string& roomName,
                            std::vector<sf::Vector2f> emptyPositions,
                            std::vector<Entity>& blocks)
{
	const auto roomWidth = getRoomJson(roomName).at("width").get<int>(),
	           roomHeight = getRoomJson(roomName).at("height").get<int>();

	for(auto i = 0; i < roomWidth; i++)
	{
		const auto posA = sf::Vector2f(i * 50.0f, 0.0f), posB = sf::Vector2f(i * 50.0f, (roomHeight - 1) * 50.0f);
		if(std::find(emptyPositions.begin(), emptyPositions.end(), posA) == emptyPositions.end()) 
			blocks.push_back(Entity(textures["block"], posA));
		if(std::find(emptyPositions.begin(), emptyPositions.end(), posB) == emptyPositions.end()) 
			blocks.push_back(Entity(textures["block"], posB));
	}

	for(auto i = 1; i < roomHeight - 1; i++)
	{
		const auto posA = sf::Vector2f(0.0f, i * 50.0f), posB = sf::Vector2f((roomWidth - 1) * 50.0f, i * 50.0f);
		if(std::find(emptyPositions.begin(), emptyPositions.end(), posA) == emptyPositions.end())
			blocks.push_back(Entity(textures["block"], posA));
		if(std::find(emptyPositions.begin(), emptyPositions.end(), posB) == emptyPositions.end())
			blocks.push_back(Entity(textures["block"], posB));
	}
}

/* Sebastian Pietras */
void Resources::createInternalBlocks(const std::string& roomName,
                                     const std::vector<sf::Vector2f>& emptyPositions,
                                     std::vector<Entity>& blocks)
{
	for(auto& entity : json(getRoomJson(roomName).at("blocks")))
	{
		const sf::Vector2f position(entity.at("positionX").get<float>(), entity.at("positionY").get<float>());
		const auto width = entity.at("width").get<int>(), height = entity.at("height").get<int>();

		for(auto i = 0; i < width; i++)
		{
			for(auto j = 0; j < height; j++)
			{
				const auto subPos = sf::Vector2f(position.x + i * 50.0f, position.y + j * 50.0f);

				if(std::find(emptyPositions.begin(), emptyPositions.end(), subPos) == emptyPositions.end())
					blocks.push_back(Entity(textures["block"], subPos));
			}
		}
	}
}

/* Sebastian Pietras */
std::vector<Entity> Resources::createBlocks(const std::string& roomName)
{
	std::vector<Entity> blocks;

	const auto emptyPos = getEmptyPositions(roomName); //where to not create blocks (like in entrances)

	//Assumes that all blocks are 50x50

	createWalls(roomName, emptyPos, blocks);
	createInternalBlocks(roomName, emptyPos, blocks);

	return blocks;
}

/*Bernard Lesiewicz, Sebastian Pietras*/
std::vector<Door> Resources::createDoors(const std::string& roomName)
{
	std::vector<Door> doors;
	for(auto& door : json(getRoomJson(roomName).at("doors")))
	{
		const sf::Vector2f position(door.at("positionX").get<float>(), door.at("positionY").get<float>());
		const auto id = door.at("id").get<int>();
		const auto opened = door.at("opened").get<bool>();
		const auto textureName = door.at("texture").get<std::string>();
		doors.push_back(Door(textures[textureName], position, id, opened));
	}
	return doors;
}

/*Bernard Lesiewicz, Sebastian Pietras */
std::vector<Key> Resources::createKeys(const std::string& roomName)
{
	std::vector<Key> keys;
	for(auto& key : json(getRoomJson(roomName).at("keys")))
	{
		const sf::Vector2f position(key.at("positionX").get<float>(), key.at("positionY").get<float>());
		const auto pickedUp = key.at("pickedUp").get<bool>();
		const auto textureName = key.at("texture").get<std::string>();
		const auto doorId = key.at("doorId").get<int>();
		const auto doorRoomName = key.at("doorRoomName").get<std::string>();
		keys.push_back(Key(textures[textureName], position, doorId, doorRoomName, pickedUp));
	}
	return keys;
}

/* Sebastian Pietras */
std::vector<std::unique_ptr<Enemy>> Resources::createEnemies()
{
	std::vector<std::unique_ptr<Enemy>> enemies;
	for(auto enemy : enemiesData)
	{
		const auto type = enemy.at("type").get<int>(), id = enemy.at("id").get<int>();
		const auto room = enemy.at("room").get<std::string>();
		const sf::Vector2f position(enemy.at("positionX").get<float>(), enemy.at("positionY").get<float>());
		const sf::Vector2f speed(enemy.at("speed").get<float>(), enemy.at("jumpSpeed").get<float>());
		const auto gravity = enemy.at("gravity").get<float>(), friction = enemy.at("friction").get<float>();

		if(type == 1)
		{
			const auto walkingRight = enemy.at("walkingRight").get<bool>();
			enemies.emplace_back(new Walker(textures["enemy1"], position, speed, gravity, friction, room, id, walkingRight));
		}
	}

	return enemies;
}

/* Sebastian Pietras */
std::unordered_map<std::string, Room> Resources::createRooms()
{
	std::unordered_map<std::string, Room> roomMap;
	for(auto room : rooms)
	{
		const auto roomName = room.at("name").get<std::string>();
		roomMap[roomName] = Room(roomName);
	}

	return roomMap;
}

/* Sebastian Pietras */
json& Resources::getRoomJson(const std::string& name)
{
	for(auto& room : rooms) { if(room.at("name").get<std::string>() == name) return room; }

	throw; //TODO: Improve this
}
