#pragma once
#include "../Entity.h"
#include "../Player.h"

class Obstacle : public Entity
{
public:
	Obstacle(sf::Texture& texture,
	         const sf::Vector2f position,
	         const std::string& roomName)
		: Entity(texture, position, roomName) { }

	virtual void update() {}
	virtual void onPlayerCollision(Player&) {}
};
