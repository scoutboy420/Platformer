#pragma once
#include "Obstacle.h"

class Laser : public Obstacle
{
	sf::Clock showClock_;

public:
	Laser(sf::Texture& texture,
	      const sf::Vector2f position,
	      const std::string& roomName)
		: Obstacle(texture, position, roomName) { }

	void onPlayerCollision(Player& player) override { player.hurt(50, player); }
	void update() override;
};
