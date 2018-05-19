#include "MobileEntity.h"

/* Sebastian Pietras, Bernard Lesiewicz */
void MobileEntity::update(const float deltaTime)
{
	velocity_.y -= gravity_ * deltaTime;

	velocity_.x *= 1.0f / (1.0f + deltaTime * friction_);

	if(std::fabs(velocity_.x) < 0.0001f) velocity_.x = 0.0f;

	const auto transform = sf::Vector2f(velocity_.x * deltaTime, velocity_.y * deltaTime);
	move(transform);
}

/* Sebastian Pietras */
void MobileEntity::jump()
{
	if(onGround)
	{
		velocity_.y = speed_.y;
		onGround = false;
	}
}

/* Sebastian Pietras, Bernard Lesiewicz */
sf::Vector2f MobileEntity::checkPush(const Entity& other, const float deltaTime) const
{
	const auto deltaX = other.getCenter().x - getCenter().x;
	const auto deltaY = other.getCenter().y - getCenter().y;
	const auto intersectX = std::fabs(deltaX) - (other.getSize().x * 0.5f + getSize().x * 0.5f);
	const auto intersectY = std::fabs(deltaY) - (other.getSize().y * 0.5f + getSize().y * 0.5f);

	if(intersectX < 0.0f && intersectY < 0.0f &&
	   (intersectX <= -fabs(deltaTime * velocity_.x) - 0.001f || intersectY <= -fabs(deltaTime * velocity_.y) - 0.001f))
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

		return {intersectX, -intersectY};
	}

	return {0.0f, 0.0f};
}
