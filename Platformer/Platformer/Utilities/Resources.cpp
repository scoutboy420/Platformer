#include "Resources.h"
#include <fstream>
#include "../Entities/Enemies/Walker.h"
#include "Room.h"
#include "../Entities/Enemies/Flier.h"
#include "../Entities/Enemies/Shooter.h"
#include "../Entities/Obstacles/Spikes.h"
#include "../Entities/Obstacles/Inverter.h"
#include "../Entities/Obstacles/Laser.h"

json Resources::rooms;
json Resources::defaultRooms;
json Resources::playerData;
json Resources::defaultPlayerData;
json Resources::enemiesData;
json Resources::defaultEnemiesData;
std::unordered_map<std::string, sf::Texture> Resources::textures;
std::unordered_map<std::string, sf::Font> Resources::fonts;

/* Sebastian Pietras */
void Resources::load()
{
	std::ifstream i;


	i.open("Data/JSON/rooms.json");
	if(!i) throw std::runtime_error("Can't open Data/Json/rooms.json");
	i >> rooms;
	i.close();
	i.clear();

	i.open("Data/JSON/player.json");
	if(!i) throw std::runtime_error("Can't open Data/Json/player.json");
	i >> playerData;
	i.close();
	i.clear();

	i.open("Data/JSON/enemies.json");
	if(!i) throw std::runtime_error("Can't open Data/Json/enemies.json");
	i >> enemiesData;
	i.close();
	i.clear();

	i.open("Data/Json/defaultrooms.json");
	if(!i) throw std::runtime_error("Can't open Data/Json/defaultrooms.json");
	i >> defaultRooms;
	i.close();
	i.clear();

	i.open("Data/Json/defaultplayer.json");
	if(!i) throw std::runtime_error("Can't open Data/Json/defaultplayer.json");
	i >> defaultPlayerData;
	i.close();
	i.clear();

	i.open("Data/Json/defaultenemies.json");
	if(!i) throw std::runtime_error("Can't open Data/Json/defaultenemies.json");
	i >> defaultEnemiesData;
	i.close();
	i.clear();


	if(!textures["player"].loadFromFile("Data/Textures/player.png")) throw std::runtime_error("Can't load texture from Data/Textures/player.png");
	if(!textures["block"].loadFromFile("Data/Textures/block.png")) throw std::runtime_error("Can't load texture from Data/Textures/block.png");
	if(!textures["walker"].loadFromFile("Data/Textures/simr.png")) throw std::runtime_error("Can't load texture from Data/Textures/simr.png");
	if(!textures["flier"].loadFromFile("Data/Textures/elektro.png")) throw std::runtime_error("Can't load texture from Data/Textures/elektro.png");
	if(!textures["shooter"].loadFromFile("Data/Textures/mini.png")) throw std::runtime_error("Can't load texture from Data/Textures/mini.png");
	if(!textures["bullet"].loadFromFile("Data/Textures/bullet.png")) throw std::runtime_error("Can't load texture from Data/Textures/bullet.png");
	if(!textures["spikes"].loadFromFile("Data/Textures/mechatro.png")) throw std::runtime_error("Can't load texture from Data/Textures/mechatro.png");
	if(!textures["laser"].loadFromFile("Data/Textures/mel.png")) throw std::runtime_error("Can't load texture from Data/Textures/mel.png");
	if(!textures["inverter"].loadFromFile("Data/Textures/fizyka.png")) throw std::runtime_error("Can't load texture from Data/Textures/fizyka.png");

	/*textures: Bernard Lesiewicz*/
	if(!textures["door_rd"].loadFromFile("Data/Textures/door_rd.png")) throw std::runtime_error("Can't load texture from Data/Textures/door_rd.png");
	if(!textures["door_gr"].loadFromFile("Data/Textures/door_gr.png")) throw std::runtime_error("Can't load texture from Data/Textures/door_gr.png");
	if(!textures["door_bl"].loadFromFile("Data/Textures/door_bl.png")) throw std::runtime_error("Can't load texture from Data/Textures/door_bl.png");
	if(!textures["door_or"].loadFromFile("Data/Textures/door_or.png")) throw std::runtime_error("Can't load texture from Data/Textures/door_or.png");
	if(!textures["door_mg"].loadFromFile("Data/Textures/door_mg.png")) throw std::runtime_error("Can't load texture from Data/Textures/door_mg.png");
	if(!textures["door_yl"].loadFromFile("Data/Textures/door_yl.png")) throw std::runtime_error("Can't load texture from Data/Textures/door_yl.png");
	if(!textures["door_wh"].loadFromFile("Data/Textures/door_wh.png")) throw std::runtime_error("Can't load texture from Data/Textures/door_wh.png");
	if(!textures["door_gy"].loadFromFile("Data/Textures/door_gy.png")) throw std::runtime_error("Can't load texture from Data/Textures/door_gy.png");
	if(!textures["door_bk"].loadFromFile("Data/Textures/door_bk.png")) throw std::runtime_error("Can't load texture from Data/Textures/door_bk.png");

	if(!textures["key_rd"].loadFromFile("Data/Textures/key_rd.png")) throw std::runtime_error("Can't load texture from Data/Textures/key_rd.png");
	if(!textures["key_gr"].loadFromFile("Data/Textures/key_gr.png")) throw std::runtime_error("Can't load texture from Data/Textures/key_gr.png");
	if(!textures["key_bl"].loadFromFile("Data/Textures/key_bl.png")) throw std::runtime_error("Can't load texture from Data/Textures/key_bl.png");
	if(!textures["key_or"].loadFromFile("Data/Textures/key_or.png")) throw std::runtime_error("Can't load texture from Data/Textures/key_or.png");
	if(!textures["key_mg"].loadFromFile("Data/Textures/key_mg.png")) throw std::runtime_error("Can't load texture from Data/Textures/key_mg.png");
	if(!textures["key_yl"].loadFromFile("Data/Textures/key_yl.png")) throw std::runtime_error("Can't load texture from Data/Textures/key_yl.png");
	if(!textures["key_wh"].loadFromFile("Data/Textures/key_wh.png")) throw std::runtime_error("Can't load texture from Data/Textures/key_wh.png");
	if(!textures["key_gy"].loadFromFile("Data/Textures/key_gy.png")) throw std::runtime_error("Can't load texture from Data/Textures/key_gy.png");
	if(!textures["key_bk"].loadFromFile("Data/Textures/key_bk.png")) throw std::runtime_error("Can't load texture from Data/Textures/key_bk.png");

	if(!textures["portal_rd"].loadFromFile("Data/Textures/portal_rd.png")) throw std::runtime_error("Can't load texture from Data/Textures/portal_rd.png");
	if(!textures["portal_gr"].loadFromFile("Data/Textures/portal_gr.png")) throw std::runtime_error("Can't load texture from Data/Textures/portal_gr.png");
	if(!textures["portal_bl"].loadFromFile("Data/Textures/portal_bl.png")) throw std::runtime_error("Can't load texture from Data/Textures/portal_bl.png");
	if(!textures["portal_or"].loadFromFile("Data/Textures/portal_or.png")) throw std::runtime_error("Can't load texture from Data/Textures/portal_or.png");
	if(!textures["portal_mg"].loadFromFile("Data/Textures/portal_mg.png")) throw std::runtime_error("Can't load texture from Data/Textures/portal_mg.png");
	if(!textures["portal_yl"].loadFromFile("Data/Textures/portal_yl.png")) throw std::runtime_error("Can't load texture from Data/Textures/portal_yl.png");
	if(!textures["portal_wh"].loadFromFile("Data/Textures/portal_wh.png")) throw std::runtime_error("Can't load texture from Data/Textures/portal_wh.png");
	if(!textures["portal_gy"].loadFromFile("Data/Textures/portal_gy.png")) throw std::runtime_error("Can't load texture from Data/Textures/portal_gy.png");
	if(!textures["portal_bk"].loadFromFile("Data/Textures/portal_bk.png")) throw std::runtime_error("Can't load texture from Data/Textures/portal_bk.png");

	if(!fonts["vcr"].loadFromFile("Data/Fonts/vcr.ttf")) throw std::runtime_error("Can't load font from Data/Fonts/vcr.ttf");
	if(!fonts["roboto"].loadFromFile("Data/Fonts/roboto.ttf")) throw std::runtime_error("Can't load font from Data/Fonts/roboto.ttf");
}

/* Sebastian Pietras */
void Resources::save()
{
	std::ofstream o;

	o.open("Data/JSON/rooms.json", std::ofstream::out | std::ofstream::trunc);
	if(!o) throw std::runtime_error("Can't open Data/Json/rooms.json");
	o << std::setw(4) << rooms;
	o.close();
	o.clear();

	o.open("Data/JSON/player.json", std::ofstream::out | std::ofstream::trunc);
	if(!o) throw std::runtime_error("Can't open Data/Json/rooms.json");
	o << std::setw(4) << playerData;
	o.close();
	o.clear();

	o.open("Data/JSON/enemies.json", std::ofstream::out | std::ofstream::trunc);
	if(!o) throw std::runtime_error("Can't open Data/Json/rooms.json");
	o << std::setw(4) << enemiesData;
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

		for(auto i = 0; i < entranceWidth; i++) { for(auto j = 0; j < entranceHeight; j++) { emptyPos.push_back(sf::Vector2f(entrancePos.x + i * 50.0f, entrancePos.y + j * 50.0f)); } }
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
		try
		{
			if(std::find(emptyPositions.begin(), emptyPositions.end(), posA) == emptyPositions.end())
				blocks.
						push_back(Entity(textures["block"], posA, roomName));
		}
		catch(const std::exception& e)
		{
			throw std::runtime_error("Can't create wall block in " + roomName + " at position " + std::to_string(posA.x)
			                         + "," +
			                         std::to_string(posA.y) + ".\n" + std::string(e.what()));
		}
		try
		{
			if(std::find(emptyPositions.begin(), emptyPositions.end(), posB) == emptyPositions.end())
				blocks.
						push_back(Entity(textures["block"], posB, roomName));
		}
		catch(const std::exception& e)
		{
			throw std::runtime_error("Can't create wall block in " + roomName + " at position " + std::to_string(posB.x)
			                         + "," +
			                         std::to_string(posB.y) + ".\n" + std::string(e.what()));
		}
	}

	for(auto i = 1; i < roomHeight - 1; i++)
	{
		const auto posA = sf::Vector2f(0.0f, i * 50.0f), posB = sf::Vector2f((roomWidth - 1) * 50.0f, i * 50.0f);
		try
		{
			if(std::find(emptyPositions.begin(), emptyPositions.end(), posA) == emptyPositions.end())
				blocks.
						push_back(Entity(textures["block"], posA, roomName));
		}
		catch(const std::exception& e)
		{
			throw std::runtime_error("Can't create wall block in " + roomName + " at position " + std::to_string(posA.x)
			                         + "," +
			                         std::to_string(posA.y) + ".\n" + std::string(e.what()));
		}
		try
		{
			if(std::find(emptyPositions.begin(), emptyPositions.end(), posB) == emptyPositions.end())
				blocks.
						push_back(Entity(textures["block"], posB, roomName));
		}
		catch(const std::exception& e)
		{
			throw std::runtime_error("Can't create wall block in " + roomName + " at position " + std::to_string(posB.x)
			                         + "," +
			                         std::to_string(posB.y) + ".\n" + std::string(e.what()));
		}
	}
}

/* Sebastian Pietras */
void Resources::createInternalBlocks(const std::string& roomName,
                                     const std::vector<sf::Vector2f>& emptyPositions,
                                     std::vector<Entity>& blocks)
{
	for(auto& entity : json(getRoomJson(roomName).at("blocks")))
	{
		try
		{
			const sf::Vector2f position(entity.at("positionX").get<float>(), entity.at("positionY").get<float>());
			const auto width = entity.at("width").get<int>(), height = entity.at("height").get<int>();

			for(auto i = 0; i < width; i++)
			{
				for(auto j = 0; j < height; j++)
				{
					const auto subPos = sf::Vector2f(position.x + i * 50.0f, position.y + j * 50.0f);

					if(std::find(emptyPositions.begin(), emptyPositions.end(), subPos) == emptyPositions.end())
						blocks.
								push_back(Entity(textures["block"], subPos, roomName));
				}
			}
		}
		catch(const std::exception& e) { throw std::runtime_error("Can't create internal block in " + roomName + ".\n" + std::string(e.what())); }
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
		try
		{
			const sf::Vector2f position(door.at("positionX").get<float>(), door.at("positionY").get<float>());
			const auto id = door.at("id").get<int>();
			const auto opened = door.at("opened").get<bool>();
			const auto textureName = door.at("texture").get<std::string>();
			doors.push_back(Door(textures[textureName], position, id, opened, roomName));
		}
		catch(const std::exception& e) { throw std::runtime_error("Can't create door in " + roomName + ".\n" + std::string(e.what())); }
	}
	return doors;
}

/*Bernard Lesiewicz, Sebastian Pietras */
std::vector<Key> Resources::createKeys(const std::string& roomName)
{
	std::vector<Key> keys;
	for(auto& key : json(getRoomJson(roomName).at("keys")))
	{
		try
		{
			const sf::Vector2f position(key.at("positionX").get<float>(), key.at("positionY").get<float>());
			const auto pickedUp = key.at("pickedUp").get<bool>();
			const auto textureName = key.at("texture").get<std::string>();
			const auto doorId = key.at("doorId").get<int>();
			const auto doorRoomName = key.at("doorRoomName").get<std::string>();
			keys.push_back(Key(textures[textureName], position, doorId, doorRoomName, pickedUp, roomName));
		}
		catch(const std::exception& e) { throw std::runtime_error("Can't create key in " + roomName + ".\n" + std::string(e.what())); }
	}
	return keys;
}

/* Bernard Lesiewicz */
std::vector<Portal> Resources::createPortals(const std::string& roomName)
{
	std::vector<Portal> portals;
	for(auto& portal : json(getRoomJson(roomName).at("portals")))
	{
		try
		{
			const sf::Vector2f position(portal.at("positionX").get<float>(), portal.at("positionY").get<float>());
			const auto id = portal.at("id").get<int>();
			const auto toId = portal.at("toId").get<int>();
			const auto toRoomName = portal.at("toRoom").get<std::string>();
			const auto textureName = portal.at("texture").get<std::string>();
			portals.push_back(Portal(textures[textureName], position, roomName, id, toId, toRoomName));
		}
		catch(const std::exception& e) { throw std::runtime_error("Can't create portal in " + roomName + ".\n" + std::string(e.what())); }
	}
	return portals;
}

std::vector<std::unique_ptr<Obstacle>> Resources::createObstacles(const std::string& roomName)
{
	std::vector<std::unique_ptr<Obstacle>> obstacles;
	for(auto& obstacle : json(getRoomJson(roomName).at("obstacles")))
	{
		try
		{
			const sf::Vector2f position(obstacle.at("positionX").get<float>(), obstacle.at("positionY").get<float>());
			const auto type = obstacle.at("type").get<int>();
			if(type == 1) obstacles.emplace_back(new Spikes(textures["spikes"], position, roomName));
			else if(type == 2) obstacles.emplace_back(new Laser(textures["laser"], position, roomName));
			else if(type == 3) obstacles.emplace_back(new Inverter(textures["inverter"], position, roomName));
		}
		catch(const std::exception& e) { throw std::runtime_error("Can't create obstacle in " + roomName + ".\n" + std::string(e.what())); }
	}
	return obstacles;
}

/* Sebastian Pietras */
std::vector<std::unique_ptr<Enemy>> Resources::createEnemies()
{
	std::vector<std::unique_ptr<Enemy>> enemies;
	for(auto& enemy : enemiesData)
	{
		const auto type = enemy.at("type").get<int>(), id = enemy.at("id").get<int>(),
		           hp = enemy.at("hp").get<int>(), damage = enemy.at("damage").get<int>();
		const auto room = enemy.at("room").get<std::string>();
		const sf::Vector2f position(enemy.at("positionX").get<float>(), enemy.at("positionY").get<float>());

		if(type == 1)
		{
			const auto speed = enemy.at("speed").get<float>();
			const auto gravity = enemy.at("gravity").get<float>(), friction = enemy.at("friction").get<float>();
			const auto walkingRight = enemy.at("walkingRight").get<bool>();
			enemies.emplace_back(new Walker(textures["walker"],
			                                position,
			                                speed,
			                                gravity,
			                                friction,
			                                room,
			                                hp,
			                                id,
			                                damage,
			                                walkingRight));
		}
		else if(type == 2)
		{
			const auto friction = enemy.at("friction").get<float>();
			enemies.emplace_back(new Flier(textures["flier"], position, friction, room, hp, id, damage));
		}
		else if(type == 3)
		{
			const auto gravity = enemy.at("gravity").get<float>();
			enemies.emplace_back(new Shooter(textures["shooter"], position, gravity, room, hp, id, damage));
		}
	}

	return enemies;
}

/* Sebastian Pietras */
std::unordered_map<std::string, Room> Resources::createRooms()
{
	std::unordered_map<std::string, Room> roomMap;
	for(auto& room : rooms)
	{
		try
		{
			const auto roomName = room.at("name").get<std::string>();
			roomMap[roomName] = Room(roomName);
		}
		catch(const std::exception& e) { throw std::runtime_error("Can't create room.\n" + std::string(e.what())); }
	}

	return roomMap;
}

/* Sebastian Pietras */
json& Resources::getRoomJson(const std::string& name)
{
	for(auto& room : rooms) if(room.at("name").get<std::string>() == name) return room;

	throw std::out_of_range("Room json for " + name + " not found");
}

/* Sebastian Pietras */
json& Resources::getEnemyJson(const int id)
{
	for(auto& enemy : enemiesData) if(enemy.at("id").get<int>() == id) return enemy;

	throw std::out_of_range("Enemy json for " + std::to_string(id) + " not found");
}

/* Sebastian Pietras */
json& Resources::getDoorJson(const std::string& roomName, const int id)
{
	for(auto& room : rooms)
		if(room.at("name").get<std::string>() == roomName)
			for(auto& door : room.at("doors"))
				if(door.at("id").get<int>() ==
					id)
					return door;

	throw std::out_of_range("Door json for " + roomName + ", " + std::to_string(id) + " not found");
}

/* Sebastian Pietras */
json& Resources::getKeyJson(const std::string& roomName, const int doorId)
{
	for(auto& room : rooms)
		if(room.at("name").get<std::string>() == roomName)
			for(auto& key : room.at("keys"))
				if(key.at("doorId").get<int>() ==
					doorId)
					return key;

	throw std::out_of_range("Key json for " + roomName + ", " + std::to_string(doorId) + " not found");
}
