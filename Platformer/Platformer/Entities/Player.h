#pragma once
#include "Entity.h"
#include "../Utilities/Resources.h"

class Player :
	public Entity
{
	sf::Vector2f velocity_, speed_, drag_;
public:
	bool onGround;

	Player() : onGround(false) { }

	Player(sf::Texture& texture, sf::Vector2f position, sf::Vector2f speed, sf::Vector2f drag) :
		Entity(texture, position), velocity_(0.0f, 0.0f), speed_(speed), drag_(drag), onGround(false) { }

	const sf::Sprite& getBody() const { return body_; }

	void update(float deltaTime);

	void jump();
	void move(sf::Vector2f transform);

	void run(Resources::direction direction)
	{
		if(direction == Resources::direction::LEFT) velocity_.x = -speed_.x;
		if(direction == Resources::direction::RIGHT) velocity_.x = speed_.x;
	}

	void stopX() { velocity_.x = 0.0f; }
	void stopY() { velocity_.y = 0.0f; }

	sf::Vector2f checkPush(const Entity& other) const;
};
