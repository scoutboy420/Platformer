#pragma once
#include "Entity.h"
#include <utility>

class MobileEntity : public Entity
{
protected:
	sf::Vector2f velocity_, speed_;
	float gravity_, friction_;
	bool onGround_;
	std::string currentRoomName_;

public:

	MobileEntity()
		: velocity_(0.0f, 0.0f)
		, speed_(0.0f, 0.0f)
		, gravity_(0.0f)
		, friction_(0.0f)
		, onGround_(false) { }

	MobileEntity(sf::Texture& texture,
	             const sf::Vector2f position,
	             const sf::Vector2f speed,
	             const float gravity,
	             const float friction,
	             std::string roomName)
		: Entity(texture, position)
		, velocity_(0.0f, 0.0f)
		, speed_(speed)
		, gravity_(gravity)
		, friction_(friction)
		, onGround_(false)
		, currentRoomName_(std::move(roomName)) { }

	sf::Vector2f getVelocity() const { return velocity_; }
	std::string getCurrentRoomName() const { return currentRoomName_; }

	virtual void update(float deltaTime);

	void jump();
	void move(const sf::Vector2f transform) { body_.move(sf::Vector2f(transform.x, -transform.y)); }
	void setPosition(const sf::Vector2f position) { body_.setPosition(position); }
	void setVelocity(const sf::Vector2f velocity) { velocity_ = velocity; }
	void stopX() { velocity_.x = 0.0f; }
	void stopY() { velocity_.y = 0.0f; }

	void run(const bool runRight)
	{
		if(!runRight) velocity_.x = -speed_.x;
		else velocity_.x = speed_.x;
	}

	virtual void onRoomChange(const std::string& roomName) { currentRoomName_ = roomName; }
	void onCollision(const Entity& colliding, sf::Vector2f push) override;
};
