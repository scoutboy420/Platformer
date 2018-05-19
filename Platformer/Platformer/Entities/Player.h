#pragma once
#include "MobileEntity.h"
#include "../Utilities/Resources.h"

class Player : public MobileEntity
{
	int healthPoints_;

public:
	Player()
		: healthPoints_(0) {}

	Player(sf::Texture& texture, const sf::Vector2f position, const sf::Vector2f speed, const float gravity, const float friction)
		: MobileEntity(texture, position, speed, gravity, friction)
		, healthPoints_(100) { }

	int getHp() const { return healthPoints_; }
	void setHp(int hp);
	bool hurt(int damage);
};
