#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Entities/Entity.h"
#include "../Entities/Misc/Key.h"
#include "../Entities/Misc/Door.h"
#include "../Entities/Misc/Portal.h"
#include "Resources.h"
#include "../Entities/Obstacles/Obstacle.h"

class Room
{
	std::string roomName_;
	std::vector<Entity> blocks_;
	std::vector<Key> keys_;
	std::vector<Door> doors_;
	std::vector<Portal> portals_;
	std::vector<std::unique_ptr<Obstacle>> obstacles_;
	sf::Color backgroundColor_;
	sf::RectangleShape background_;
	sf::Vector2f size_; //size of room from 0,0 to bottom right corner of bottom right block

	std::vector<std::vector<sf::Vertex>> gradientEdges_{}; //effect of fading to black on edges od the room

	void addGradient();
public:
	Room() = default;
	explicit Room(const std::string& roomName, bool def = false);

	std::string getRoomName() const { return roomName_; }
	sf::Vector2f getSize() const { return size_; }
	const std::vector<Entity>& getEntities() const { return blocks_; }
	std::vector<Key>& getKeys() { return keys_; }
	std::vector<Door>& getDoors() { return doors_; }
	std::vector<Portal>& getPortals() { return portals_; }
	std::vector<std::unique_ptr<Obstacle>>& getObstacles() { return obstacles_; }
	std::vector<std::vector<sf::Vertex>> getGradientEdges() const { return gradientEdges_; }
	sf::Color getBackgroundColor() const { return backgroundColor_; }
	sf::RectangleShape getBackground() const { return background_; }

	void update() { for(auto& obstacle : obstacles_) obstacle->update(); }
};
