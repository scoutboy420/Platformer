#include "Room.h"
#include "Resources.h"

Room::Room(int roomId)
{
	blocks_ = Resources::createEntities(roomId);

	//calculateSize();

	const std::string roomName = "room" + std::to_string(roomId);

	const int r = Resources::rooms_.at(roomName).at("colorR").get<int>();
	const int g = Resources::rooms_.at(roomName).at("colorG").get<int>();
	const int b = Resources::rooms_.at(roomName).at("colorB").get<int>();

	background_ = sf::Color(r, g, b);
}
