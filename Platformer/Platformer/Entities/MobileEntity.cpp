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
	if(onGround_)
	{
		velocity_.y = speed_.y;
		onGround_ = false;
	}
}

/* Sebastian Pietras */
void MobileEntity::onCollision(const Entity&, const sf::Vector2f push)
{
	if(push.y > 0) //if it pushes the entity upwards, then the entity is on top of something
	{
		onGround_ = true;
		stopY();
	}
	if(fabs(push.x) > 0) stopX();
}
