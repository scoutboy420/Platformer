#pragma once
#include "MobileEntity.h"

class Player : public MobileEntity
{
public:
	Player() = default;

	Player(sf::Texture& texture,
	       const sf::Vector2f position,
	       const sf::Vector2f speed,
	       const float gravity,
	       const float friction,
	       const std::string& roomName)
		: MobileEntity(texture, position, speed, gravity, friction, roomName, 100) { }


	void update(float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&) override;
	void onRoomChange(const std::string& roomName) override;
};
