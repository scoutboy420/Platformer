#pragma once

/**
* @file
* @brief Player class
*/

#include "MobileEntity.h"

class Player : public MobileEntity
{
	sf::Clock dashCooldown_;
	sf::Clock dashClock_;
	sf::Clock shootClock_;
	sf::Clock manaCooldown_;
	sf::Clock invertClock_;
	float dashSpeed_;
	int dashDamage_;
	bool movingRight_;
	float mana_;
	bool startInvertGuard_;
	bool startDashGuard_;
public:
	Player()
		: dashSpeed_(0)
		, dashDamage_(0)
		, movingRight_(true)
		, mana_(0)
		, startInvertGuard_(true)
		, startDashGuard_(true) {}

	/**
	 * \brief Constructs player
	 * \param texture Texture
	 * \param position Position vector
	 * \param speed Speed vector, where x is vertical speed and y is horizontal speed (jump speed)
	 * \param gravity Gravity value
	 * \param friction Friction value
	 * \param roomName Name of the room where the entity is
	 * \param hp Health points
	 * \param mana Mana points
	 * \param dashSpeed Vertical speed of dash
	 * \param dashDamage Damage done when dashing
	 */
	Player(sf::Texture& texture,
	       const sf::Vector2f position,
	       const sf::Vector2f speed,
	       const float gravity,
	       const float friction,
	       const std::string& roomName,
	       const int hp,
	       const float mana,
	       const float dashSpeed,
	       const int dashDamage)
		: MobileEntity(texture, position, speed, gravity, friction, roomName, hp)
		, dashSpeed_(dashSpeed)
		, dashDamage_(dashDamage)
		, movingRight_(true)
		, mana_(mana)
		, startInvertGuard_(true)
		, startDashGuard_(true) { }

	void dash();
	bool isDashing() const { return dashClock_.getElapsedTime().asSeconds() <= 0.125f && !startDashGuard_; }
	int getDashDamage() const { return dashDamage_; }

	void shoot(std::vector<Bullet>& bullets);

	bool isImmune() const override { return MobileEntity::isImmune() || isDashing(); }
	bool isInverted() const { return invertClock_.getElapsedTime().asSeconds() <= 5.0f && !startInvertGuard_; }

	bool hurt(int damage, Player&) override;

	void heal(int amount);
	void addMana(float amount);
	float getMana() const { return mana_; }

	void run(bool runRight) override;
	void jump(bool force) override;

	void invert();

	void update(float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&) override;
	void onRoomChange(const std::string& roomName) override;
};
