#pragma once
#include "MobileEntity.h"
#include "../Utilities/Resources.h"

class Player :
	public MobileEntity
{
	int healthPoints_;

public:
	Player() : healthPoints_(0){}

	Player(sf::Texture& texture, sf::Vector2f position, sf::Vector2f speed, float gravity, float friction) :
		MobileEntity(texture, position, speed, gravity, friction), healthPoints_(100){ }

	int getHp() const { return healthPoints_; }
	void setHp(int hp);
	bool hurt(int damage);
};
