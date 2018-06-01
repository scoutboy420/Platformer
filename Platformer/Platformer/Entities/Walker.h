#pragma once
#include "Enemy.h"

class Walker : public Enemy
{
	bool walkRight_;

public:
	Walker(sf::Texture& texture,
	       const sf::Vector2f position,
	       const float speedX,
	       const float gravity,
	       const float friction,
	       const std::string& roomName,
	       const int id,
	       const bool walkingRight)
		: Enemy(texture, position, sf::Vector2f(speedX, 800.0f), gravity, friction, roomName, id, 10)
		, walkRight_(walkingRight) { }

	void onCollision(const Entity& colliding, sf::Vector2f push) override;

	void update(float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&) override;
};
