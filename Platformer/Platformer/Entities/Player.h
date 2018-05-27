#pragma once
#include "MobileEntity.h"

class Player : public MobileEntity
{
	int healthPoints_;

public:
	Player()
		: healthPoints_(0) {}

	Player(sf::Texture& texture,
	       const sf::Vector2f position,
	       const sf::Vector2f speed,
	       const float gravity,
	       const float friction,
	       const std::string& roomName)
		: MobileEntity(texture, position, speed, gravity, friction, roomName)
		, healthPoints_(100) { }

	int getHp() const { return healthPoints_; }
	void setHp(int hp);
	bool hurt(int damage);

	void onRoomChange(const std::string& roomName) override;
};
