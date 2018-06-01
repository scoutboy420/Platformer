#pragma once
#include "Entity.h"

class Player;

class Bullet : public Entity
{
	sf::Vector2f velocity_;
	int damage_;
public:
	Bullet(sf::Texture& texture,
	       sf::Vector2f position,
	       sf::Vector2f target,
	       int damage,
	       const std::string& roomName);

	void update(const float deltaTime) { body_.move(velocity_ * deltaTime); }

	void onPlayerCollision(Player& player) const;
	void onRoomChange(const std::string& roomName) override { currentRoomName_ = roomName; }
};
