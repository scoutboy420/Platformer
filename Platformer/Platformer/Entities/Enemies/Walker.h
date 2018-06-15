#pragma once

/**
* @file
* @brief Walker enemy class
*/

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
	       const int hp,
	       const int id,
	       const int damage,
	       const bool walkingRight)
		: Enemy(texture, position, sf::Vector2f(speedX, 800.0f), gravity, friction, roomName, hp, id, damage)
		, walkRight_(walkingRight) { }

	void onCollision(const Entity& colliding, sf::Vector2f push) override;

	void update(float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&) override;

	void saveData(json& enemyJson) override;
};
