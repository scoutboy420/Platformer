#pragma once
#include "Entity.h"
#include "../Utilities/Resources.h"

class MobileEntity : public Entity
{
	sf::Vector2f velocity_, speed_;
	float gravity_, friction_;

public:
	bool onGround;

	MobileEntity()
		: velocity_(0.0f, 0.0f)
		, speed_(0.0f, 0.0f)
		, gravity_(0.0f)
		, friction_(0.0f)
		, onGround(false) { }

	MobileEntity(sf::Texture& texture, const sf::Vector2f position, const sf::Vector2f speed, const float gravity, const float friction)
		: Entity(texture, position)
		, velocity_(0.0f, 0.0f)
		, speed_(speed)
		, gravity_(gravity)
		, friction_(friction)
		, onGround(false) { }

	sf::Vector2f getVelocity() const { return velocity_; }

	void update(float deltaTime);

	void jump();
	void move(const sf::Vector2f transform) { body_.move(sf::Vector2f(transform.x, -transform.y)); }
	void setPosition(const sf::Vector2f position) { body_.setPosition(position); }
	void stopX() { velocity_.x = 0.0f; }
	void stopY() { velocity_.y = 0.0f; }

	void run(const Resources::direction direction)
	{
		if(direction == Resources::direction::LEFT) velocity_.x = -speed_.x;
		if(direction == Resources::direction::RIGHT) velocity_.x = speed_.x;
	}

	sf::Vector2f checkPush(const Entity& other, float deltaTime) const;
};
