#pragma once
#include <vector>
#include "../Entities/Entity.h"
#include "../Entities/Door.h"
#include "../Entities/Key.h"
#include "../Entities/Enemy.h"

class Room
{
	std::string roomName_;
	std::vector<Entity> blocks_;
	std::vector<Key> keys_;
	std::vector<Door> doors_;
	sf::Color backgroundColor_;
	sf::RectangleShape background_;
	sf::Vector2f size_; //size of room from 0,0 to bottom right corner of bottom right block

	std::vector<std::vector<sf::Vertex>> gradientEdges_; //effect of fading to black on edges od the room

	std::vector<Enemy*> enemies_;

	void addGradient();
public:
	Room() = default;
	Room(const std::string& roomName, const std::vector<bool>& openedDoors);

	std::string getRoomName() const { return roomName_; }
	sf::Vector2f getSize() const { return size_; }
	const std::vector<Entity>& getEntities() const { return blocks_; }
	const std::vector<Key>& getKeys() const { return keys_; }
	const std::vector<Door>& getDoors() const { return doors_; }
	std::vector<std::vector<sf::Vertex>> getGradientEdges() const { return gradientEdges_; }
	sf::Color getBackgroundColor() const { return backgroundColor_; }
	sf::RectangleShape getBackground() const { return background_; }
	const std::vector<Enemy*>& getEnemies() const { return enemies_; }
};
