#pragma once

/**
* @file
* @brief Abstract mobile entity class, representing entities with rigid bodies (e.g. affected by gravity)
*/

#include "Entity.h"
#include "Bullet.h"

class MobileEntity : public Entity
{
protected:
	sf::Vector2f velocity_, speed_;
	float gravity_, friction_;
	bool onGround_;
	int healthPoints_;
	sf::Clock immunityClock_;
	sf::Text healthText_;

	void updateText();
public:

	MobileEntity()
		: velocity_(0.0f, 0.0f)
		, speed_(0.0f, 0.0f)
		, gravity_(0.0f)
		, friction_(0.0f)
		, onGround_(false)
		, healthPoints_(0) { }

	/**
	 * \brief Constructs a mobile entity
	 * \param texture Texture
	 * \param position Position vector
	 * \param speed Speed vector, where x is vertical speed and y is horizontal speed (jump speed)
	 * \param gravity Gravity value
	 * \param friction Friction value
	 * \param roomName Name of the room where the entity is
	 * \param hp Health points
	 */
	MobileEntity(sf::Texture& texture,
	             sf::Vector2f position,
	             sf::Vector2f speed,
	             float gravity,
	             float friction,
	             const std::string& roomName,
	             int hp);

	sf::Vector2f getVelocity() const { return velocity_; }

	virtual void update(float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&);

	virtual void jump(bool force);

	/**
	 * \brief Changes position by given transformation vector
	 * \param transform Transformation vector
	 */
	void move(const sf::Vector2f transform) { body_.move(sf::Vector2f(transform.x, -transform.y)); }
	void setVelocity(const sf::Vector2f velocity) { velocity_ = velocity; }
	void stopX() { velocity_.x = 0.0f; }
	void stopY() { velocity_.y = 0.0f; }

	sf::Text getHealthText() const { return healthText_; }

	int getHp() const { return healthPoints_; }
	void setHp(int hp);
	virtual bool hurt(int damage, Player&);
	virtual bool isImmune() const { return immunityClock_.getElapsedTime().asSeconds() <= 1.0f; }

	virtual void run(const bool runRight)
	{
		if(!runRight) velocity_.x = -speed_.x;
		else velocity_.x = speed_.x;
	}

	void onRoomChange(const std::string& roomName) override { currentRoomName_ = roomName; }
	void onCollision(const Entity& colliding, sf::Vector2f push) override;
};
