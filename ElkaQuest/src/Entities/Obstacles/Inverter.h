#pragma once

/**
* @file
* @brief Inverter obstacle class
*/

#include "Obstacle.h"

class Inverter : public Obstacle
{
public:
	Inverter(sf::Texture& texture,
	         const sf::Vector2f position,
	         const std::string& roomName)
		: Obstacle(texture, position, roomName) { }

	void onPlayerCollision(Player& player) override { player.invert(); }
};
