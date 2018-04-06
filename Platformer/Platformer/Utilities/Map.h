#pragma once
#include "Room.h"
#include <vector>

class Map
{
private:
	std::vector<std::vector<int>> roomMatrix_;
	std::vector<std::vector<std::vector<int>>> roomsStructure_;
	sf::Image mapImage_;
public:
	Map(std::vector<Room>& rooms);
};
