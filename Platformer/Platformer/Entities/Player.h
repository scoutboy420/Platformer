#pragma once
#include "MobileEntity.h"

class Player : public MobileEntity
{
	sf::Clock dashCooldown_;
	sf::Clock dashClock_;
	sf::Clock shootClock_;
	sf::Clock manaCooldown_;
	float dashSpeed_;
	int dashDamage_;
	bool movingRight_;
	float mana_;
public:
	Player()
		: dashSpeed_(0)
		, dashDamage_(0)
		, movingRight_(true)
		, mana_(0) {}

	Player(sf::Texture& texture,
	       const sf::Vector2f position,
	       const sf::Vector2f speed,
	       const float gravity,
	       const float friction,
	       const std::string& roomName)
		: MobileEntity(texture, position, speed, gravity, friction, roomName, 100)
		, dashSpeed_(2000)
		, dashDamage_(25)
		, movingRight_(true)
		, mana_(100) { }

	void dash();
	bool isDashing() const { return dashClock_.getElapsedTime().asSeconds() <= 0.125f; }
	int getDashDamage() const { return dashDamage_; }

	void shoot(std::vector<Bullet>& bullets);

	bool hurt(int damage, Player&) override;
	bool isImmune() const override { return MobileEntity::isImmune() || isDashing(); }

	void heal(int amount);
	void addMana(float amount);
	float getMana() const { return mana_; }

	void run(bool runRight) override;

	void update(float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&) override;
	void onRoomChange(const std::string& roomName) override;
};
