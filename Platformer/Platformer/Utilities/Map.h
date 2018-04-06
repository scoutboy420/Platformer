#pragma once
#include "Room.h"
#include <vector>

class Map
{
private:
	std::vector<Room> rooms_;
	sf::Texture mapTexture_;
public:
	Map(std::vector<Room>& rooms);
};