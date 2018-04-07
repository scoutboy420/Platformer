#pragma once
#include <vector>
#include "../Entities/Entity.h"

class Room
{
	std::vector<Entity> blocks_;
	sf::Color background_;
	sf::Vector2u size_;

	void calculateSize(); //TODO: implement. should calculate the size of the map by blocks
public:
	Room() = default;
	Room(int roomId);

	sf::Vector2u getSize() const { return size_; }
	const std::vector<Entity>& getEntities() const { return blocks_; }
	sf::Color getBackground() const { return background_; }
};
