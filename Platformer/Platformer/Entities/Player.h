#pragma once
#include "Entity.h"
#include "../Utilities/Resources.h"

class Player :
	public Entity
{
	sf::Vector2f velocity_, speed_;
	float gravity_, friction_;
public:
	bool onGround;

	Player() : velocity_(0.0f, 0.0f), speed_(0.0f, 0.0f), gravity_(0.0f), friction_(0.0f), onGround(false) { }

	Player(sf::Texture& texture, sf::Vector2f position, sf::Vector2f speed, float gravity, float friction) :
		Entity(texture, position), velocity_(0.0f, 0.0f), speed_(speed), gravity_(gravity), friction_(friction),
		onGround(false) { }

	const sf::Sprite& getBody() const { return body_; }

	void update(float deltaTime);

	void jump();
	void move(sf::Vector2f transform);
	void stopX() { velocity_.x = 0.0f; }
	void stopY() { velocity_.y = 0.0f; }

	void run(Resources::direction direction)
	{
		if(direction == Resources::direction::LEFT) velocity_.x = -speed_.x;
		if(direction == Resources::direction::RIGHT) velocity_.x = speed_.x;
	}

	sf::Vector2f checkPush(const Entity& other) const;
};
