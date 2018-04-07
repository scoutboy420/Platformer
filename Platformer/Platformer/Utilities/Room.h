#pragma once
#include <vector>
#include "../Entities/Entity.h"

class Room
{
	std::vector<Entity> blocks_;
	sf::Color background_;
public:
	Room() = default;
	Room(int roomId);

	sf::Vector2f getSize() const;
	const std::vector<Entity>& getEntities() const { return blocks_; }
	sf::Color getBackground() const { return background_; }
};
