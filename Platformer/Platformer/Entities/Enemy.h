#pragma once
#include "MobileEntity.h"

class Enemy : public MobileEntity
{
protected:
	int id_;
	int healthPoints_;

public:
	Enemy()
		: id_(0)
		, healthPoints_(0) {}

	Enemy(sf::Texture& texture,
	      const sf::Vector2f position,
	      const sf::Vector2f speed,
	      const float gravity,
	      const float friction,
	      const std::string& roomName,
	      const int id)
		: MobileEntity(texture, position, speed, gravity, friction, roomName)
		, id_(id)
		, healthPoints_(100) { }

	int getHp() const { return healthPoints_; }
	void setHp(int hp);
	bool hurt(int damage);

	int getId() const { return id_; }
};
