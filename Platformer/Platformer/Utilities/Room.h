#pragma once
#include <vector>
#include "../Entities/Entity.h"
#include "../Entities/Item.h"
#include "../Entities/Door.h"

class Room
{
private:
	std::vector<Entity> blocks_;
	std::vector<Item> items_;
	std::vector<Door> doors_;
	sf::Color backgroundColor_;
	bool visited_;
	sf::Vector2f size_;
	sf::Vector2i roomID_;
public:
	Room(std::vector<Entity>& blocks, std::vector<Item>& items, std::vector<Door>& doors, sf::Vector2i roomID,
	     sf::Color backgroundColor = sf::Color::White);

	sf::Vector2f getSize() const { return size_; }
	const std::vector<Entity>& getBlocks() const { return blocks_; }
	const std::vector<Item>& getItems() const { return items_; }
	const std::vector<Door>& getDoors() const { return doors_; }
	sf::Color getBackgroundColor() const { return backgroundColor_; }
};
