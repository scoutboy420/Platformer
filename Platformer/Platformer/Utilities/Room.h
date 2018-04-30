#pragma once
#include <vector>
#include "../Entities/Entity.h"

class Room
{
	int id_;
	std::vector<Entity> blocks_;
	sf::Color backgroundColor_;
	sf::RectangleShape background_;
	sf::Vector2f size_; //size of room from 0,0 to bottom right corner of bottom right block

	std::vector<std::vector<sf::Vertex>> gradientEdges_;

	void calculateSize();
	void addGradient();
public:
	Room() = default;
	Room(int roomId);

	int getID() const { return id_; }
	sf::Vector2f getSize() const { return size_; }
	const std::vector<Entity>& getEntities() const { return blocks_; }
	std::vector<std::vector<sf::Vertex>> getGradientEdges() const { return gradientEdges_; }
	sf::Color getBackgroundColor() const { return backgroundColor_; }
	sf::RectangleShape getBackground() const { return background_; }
};
