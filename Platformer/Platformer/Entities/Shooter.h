#pragma once
#include "Enemy.h"
#include "Bullet.h"

class Shooter : public Enemy
{
	sf::Clock shootClock_;
public:
	Shooter(sf::Texture& texture,
	        const sf::Vector2f position,
	        const float gravity,
	        const std::string& roomName,
	        const int id)
		: Enemy(texture, position, sf::Vector2f(0.0f, 800.0f), gravity, 0.0f, roomName, id, 5) { }

	void update(float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&) override;
};
