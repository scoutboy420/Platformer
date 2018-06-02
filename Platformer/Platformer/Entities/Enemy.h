#pragma once
#include "MobileEntity.h"

class Enemy : public MobileEntity
{
protected:
	int id_;
	int damage_;

public:
	Enemy()
		: id_(0)
		, damage_(0) {}

	Enemy(sf::Texture& texture,
	      const sf::Vector2f position,
	      const sf::Vector2f speed,
	      const float gravity,
	      const float friction,
	      const std::string& roomName,
	      const int id,
	      const int damage)
		: MobileEntity(texture, position, speed, gravity, friction, roomName, 50)
		, id_(id)
		, damage_(damage) { }

	int getId() const { return id_; }

	bool hurt(int damage, Player&) override;
	bool isImmune() const override { return immunityClock_.getElapsedTime().asSeconds() <= 0.1f; }

	virtual void onPlayerCollision(Player& player, sf::Vector2f push);
};
