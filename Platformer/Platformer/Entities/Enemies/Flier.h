#pragma once

/**
* @file
* @brief Flier enemy class
*/

/** @cond */
#include <random>
/** @endcond */
#include "Enemy.h"

class Flier : public Enemy
{
	std::mt19937 e2_;
	std::normal_distribution<> dist_;
	sf::Clock movingClock_;
public:
	Flier(sf::Texture& texture,
	      const sf::Vector2f position,
	      const float friction,
	      const std::string& roomName,
	      const int hp,
	      const int id,
	      const int damage)
		: Enemy(texture, position, sf::Vector2f(0.0f, 500.0f), 0.0f, friction, roomName, hp, id, damage)
		, e2_(std::random_device()())
		, dist_(0, 5) { }

	void update(float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&) override;
};
