#pragma once
#include "Enemy.h"

class Walker : public Enemy
{
	bool walkRight_;

public:
	Walker(sf::Texture& texture,
	       const sf::Vector2f position,
	       const sf::Vector2f speed,
	       const float gravity,
	       const float friction,
	       const std::string& roomName,
	       const int id,
	       const bool walkingRight)
		: Enemy(texture, position, speed, gravity, friction, roomName, id)
		, walkRight_(walkingRight) { }

	void onCollision(const Entity& colliding, sf::Vector2f push) override;

	void update(float deltaTime) override;
};
