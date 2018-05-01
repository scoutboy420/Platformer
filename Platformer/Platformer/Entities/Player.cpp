#include "Player.h"

void Player::update(float deltaTime)
{
	velocity_.y -= gravity_ * deltaTime;

	velocity_.x *= 1.0f / (1.0f + deltaTime * friction_);

	if(std::fabs(velocity_.x) < 0.0001f) velocity_.x = 0.0f;

	printf("Velocity: %f,%f\n", velocity_.x, velocity_.y);

	const sf::Vector2f transform = sf::Vector2f(velocity_.x * deltaTime, velocity_.y * deltaTime);
	move(transform);
}

void Player::jump()
{
	if(onGround)
	{
		velocity_.y = speed_.y;
		onGround = false;
	}
}

sf::Vector2f Player::checkPush(const Entity& other) const
{
	const float deltaX = other.getCenter().x - getCenter().x;
	const float deltaY = other.getCenter().y - getCenter().y;
	const float intersectX = std::fabs(deltaX) - (other.getSize().x * 0.5f + getSize().x * 0.5f);
	const float intersectY = std::fabs(deltaY) - (other.getSize().y * 0.5f + getSize().y * 0.5f);

	if(intersectX < 0.0f && intersectY < 0.0f)
	{
		if(intersectX > intersectY)
		{
			if(deltaX > 0.0f) return {intersectX, 0.0f};
			return {-intersectX, 0.0f};
		}
		if(intersectX < intersectY)
		{
			if(deltaY > 0.0f) return {0.0f, -intersectY};
			return {0.0f, intersectY};
		}

		return { intersectX, -intersectY };
	}

	return {0.0f, 0.0f};
}
