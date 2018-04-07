#include "Player.h"

void Player::update(float deltaTime)
{
	velocity_.y -= drag_.y * deltaTime;

	if(velocity_.x > 0) velocity_.x -= drag_.x * deltaTime;
	if(velocity_.x < 0) velocity_.x += drag_.x * deltaTime;

	sf::Vector2f transform = sf::Vector2f(velocity_.x * deltaTime, velocity_.y * deltaTime);
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

void Player::move(sf::Vector2f transform)
{
	body_.move(sf::Vector2f(transform.x, -transform.y));
}

sf::Vector2f Player::checkPush(const Entity& other) const
{
	/*float diffX = getCenter().x - other.getCenter().x;
	float diffY = getCenter().y - other.getCenter().y;

	if(std::fabs(diffX) >= std::fabs(diffY))
	{
		if(std::fabs(diffX) < getSize().x || std::fabs(diffX) < other.getSize().x)
		{
			if(diffX < 0) return { -(other.getSize().x*0.5f + getSize().x*0.5f - std::fabs(diffX)), 0.0f };
			return { other.getSize().x*0.5f + getSize().x*0.5f - std::fabs(diffX), 0.0f };
		}
	}

	if(std::fabs(diffY) < getSize().y || std::fabs(diffY) < other.getSize().y)
	{
		if(diffY < 0) return { 0.0f , other.getSize().y*0.5f + getSize().y*0.5f - std::fabs(diffY) };
		return { 0.0f, -(other.getSize().y*0.5f + getSize().y*0.5f - std::fabs(diffY)) };
	}

	return { 0.0f, 0.0f };*/

	float deltaX = other.getCenter().x - getCenter().x;
	float deltaY = other.getCenter().y - getCenter().y;
	float intersectX = std::fabs(deltaX) - (other.getSize().x * 0.5f + getSize().x * 0.5f);
	float intersectY = std::fabs(deltaY) - (other.getSize().y * 0.5f + getSize().y * 0.5f);

	if(intersectX < 0.0f && intersectY < 0.0f)
	{
		if(intersectX > intersectY)
		{
			if(deltaX > 0.0f) return {intersectX, 0.0f};
			else return {-intersectX, 0.0f};
		}
		else
		{
			if(deltaY > 0.0f) return {0.0f, -intersectY};
			else return {0.0f, intersectY};
		}
	}

	return {0.0f, 0.0f};
}
