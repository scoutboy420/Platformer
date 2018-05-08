#pragma once
#include <vector>
#include "../Entities/Entity.h"
#include "../Entities/Door.h"
#include "../Entities/Key.h"

class Room
{
	int id_;
	std::vector<Entity> blocks_;
	std::vector<Key> keys_;
	std::vector<Door> doors_;
	sf::Color backgroundColor_;
	sf::RectangleShape background_;
	sf::Vector2f size_; //size of room from 0,0 to bottom right corner of bottom right block

	std::vector<std::vector<sf::Vertex>> gradientEdges_; //effect of fading to black on edges od the room

	void addGradient();
public:
	Room() = default;
	Room(int roomId, std::vector<bool> openedDoors_);

	int getID() const { return id_; }
	sf::Vector2f getSize() const { return size_; }
	const std::vector<Entity>& getEntities() const { return blocks_; }
	const std::vector<Key>& getKeys() const { return keys_; }
	const std::vector<Door>& getDoors() const { return doors_; }
	std::vector<std::vector<sf::Vertex>> getGradientEdges() const { return gradientEdges_; }
	sf::Color getBackgroundColor() const { return backgroundColor_; }
	sf::RectangleShape getBackground() const { return background_; }
};
