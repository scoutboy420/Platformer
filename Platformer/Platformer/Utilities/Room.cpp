#include "Room.h"
#include "Resources.h"

Room::Room(int roomId)
{
	blocks_ = Resources::createEntities(roomId);

	//calculateSize();

	std::string roomName = "room" + std::to_string(roomId);

	int R = Resources::rooms_.at(roomName).at("colorR").get<int>();
	int G = Resources::rooms_.at(roomName).at("colorG").get<int>();
	int B = Resources::rooms_.at(roomName).at("colorB").get<int>();

	background_ = sf::Color(R, G, B);
}
