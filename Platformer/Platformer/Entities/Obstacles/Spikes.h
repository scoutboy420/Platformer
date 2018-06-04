#pragma once
#include "Obstacle.h"

class Spikes : public Obstacle
{
public:
	Spikes(sf::Texture& texture,
	       const sf::Vector2f position,
	       const std::string& roomName)
		: Obstacle(texture, position, roomName) { }

	void onPlayerCollision(Player& player) override { player.hurt(30, player); }
};
