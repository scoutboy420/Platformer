#pragma once
#include "MobileEntity.h"

class Player : public MobileEntity
{
	sf::Clock dashCooldown_;
	sf::Clock dashClock_;
	float dashSpeed_;
	int dashDamage_;
	bool movingRight_;
public:
	Player()
		: dashSpeed_(0)
		, dashDamage_(0)
		, movingRight_(true) {}

	Player(sf::Texture& texture,
	       const sf::Vector2f position,
	       const sf::Vector2f speed,
	       const float gravity,
	       const float friction,
	       const std::string& roomName)
		: MobileEntity(texture, position, speed, gravity, friction, roomName, 100)
		, dashSpeed_(2000)
		, dashDamage_(25)
		, movingRight_(true) { }

	void dash();
	bool isDashing() const { return dashClock_.getElapsedTime().asSeconds() <= 0.1f; }
	int getDashDamage() const { return dashDamage_; }

	bool hurt(int damage) override;
	bool isImmune() const override { return MobileEntity::isImmune() || isDashing(); }

	void run(bool runRight) override;
	//void changeRoom(const std::string& roomName) { currentRoomName_ = roomName;}

	void update(float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&) override;
	void onRoomChange(const std::string& roomName) override;
};
