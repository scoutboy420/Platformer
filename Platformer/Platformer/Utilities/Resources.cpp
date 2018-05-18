#include "Resources.h"
#include <fstream>

json Resources::rooms;
json Resources::playerData;
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

	textures["player"].loadFromFile("Data/Textures/player.png");
	textures["block"].loadFromFile("Data/Textures/block.png");

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
}

/* Sebastian Pietras */
std::vector<Entity> Resources::createEntities(int roomId)
{
	std::vector<Entity> entities;
	const std::string roomName = "room" + std::to_string(roomId);

	std::vector<sf::Vector2f> emptyPos; //where to not create blocks (like in entrances)

	for(const auto& entrances : rooms.at(roomName).at("entrances"))
	{
		const auto entranceWidth = entrances.at("width").get<int>(), entranceHeight = entrances.at("height").get<int>();
		const sf::Vector2f entrancePos = sf::Vector2f(entrances.at("x").get<float>(), entrances.at("y").get<float>());

		for(int i = 0; i < entranceWidth; i++)
		{
			for(int j = 0; j < entranceHeight; j++)
			{
				emptyPos.push_back(sf::Vector2f(entrancePos.x + i * 50.0f, entrancePos.y + j * 50.0f));
			}
		}
	}

	//Assumes that all blocks are 50x50

	const auto roomWidth = rooms.at(roomName).at("width").get<int>(), roomHeight = rooms.at(roomName).at("height").get<int>();

	for(int i = 0; i < roomWidth; i++)
	{
		const sf::Vector2f posA = sf::Vector2f(i*50.0f, 0.0f), posB = sf::Vector2f(i*50.0f, (roomHeight - 1)*50.0f);
		if(std::find(emptyPos.begin(), emptyPos.end(), posA) == emptyPos.end())
			entities.push_back(Entity(textures["block"], posA));
		if(std::find(emptyPos.begin(), emptyPos.end(), posB) == emptyPos.end())
			entities.push_back(Entity(textures["block"], posB));
	}

	for(int i = 1; i < roomHeight - 1; i++)
	{
		const sf::Vector2f posA = sf::Vector2f(0.0f, i*50.0f), posB = sf::Vector2f((roomWidth-1)*50.0f, i*50.0f);
		if(std::find(emptyPos.begin(), emptyPos.end(), posA) == emptyPos.end())
			entities.push_back(Entity(textures["block"], posA));
		if(std::find(emptyPos.begin(), emptyPos.end(), posB) == emptyPos.end())
			entities.push_back(Entity(textures["block"], posB));
	}

	for(auto& entity : rooms.at(roomName).at("entities"))
	{
		const sf::Vector2f position(entity.at("positionX").get<float>(), entity.at("positionY").get<float>());
		const auto width = entity.at("width").get<int>(), height = entity.at("height").get<int>();

		for(int i = 0; i < width; i++)
		{
			for(auto j = 0; j < height; j++)
			{
				const auto subPos = sf::Vector2f(position.x + i * 50.0f, position.y + j * 50.0f);

				if(std::find(emptyPos.begin(), emptyPos.end(), subPos) == emptyPos.end())
					entities.push_back(Entity(textures["block"], subPos));
			}
		}
	}

	return entities;
}

/*Bernard Lesiewicz*/
std::vector<Door> Resources::createDoors(int roomId, std::vector<bool> openedDoors_)
{
    std::vector<Door> doors;
	const std::string roomName = "room" + std::to_string(roomId);
	for(auto& door : rooms.at(roomName).at("doors"))
	{
		const sf::Vector2f position(door.at("positionX").get<float>(), door.at("positionY").get<float>());

		const auto id = door.at("id").get<int>();
        if(!openedDoors_[id])
        {
            doors.push_back(Door(textures[door.at("texture").get<std::string>()], position, id));
        }
	}
	return doors;
}

/*Bernard Lesiewicz*/
std::vector<Key> Resources::createKeys(int roomId, std::vector<bool> openedDoors_)
{
    std::vector<Key> keys;
	const std::string roomName = "room" + std::to_string(roomId);
	for(auto& key : rooms.at(roomName).at("keys"))
	{
		const sf::Vector2f position(key.at("positionX").get<float>(), key.at("positionY").get<float>());
		const auto id = key.at("id").get<int>();

        if(!openedDoors_[id])
        {
            keys.push_back(Key(textures[key.at("texture").get<std::string>()], position, id));
        }
	}
	return keys;
}

/*Sebastian Pietras*/
int Resources::countRooms()
{
	int i = 0;

	for(json::iterator it = rooms.begin(); it != rooms.end(); ++it)
	{
		if(it.key().find("room") != std::string::npos) i++;
	}

	return i;
}

/* Sebastian Pietras */
int Resources::getRoomId(const std::string& roomName)
{
	const auto num = roomName.substr(4);

	return std::stoi(num);
}

/*Bernard Lesiewicz*/
int Resources::highestDoorId()
{
    int lastDoor = 0;
    //int r = countRooms();
    for(int roomId = 1, r = countRooms(); roomId <= r; roomId++)
    {
        const std::string roomName = "room" + std::to_string(roomId);
        for(auto& key : rooms.at(roomName).at("doors"))
        {
            lastDoor = std::max(lastDoor, key.at("id").get<int>());
        }
	}
	return lastDoor;
}
