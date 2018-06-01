#include "MobileEntity.h"

/* Sebastian Pietras, Bernard Lesiewicz */
void MobileEntity::update(const float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&)
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
	}
	if(fabs(push.y) > 0) stopY();
	if(fabs(push.x) > 0) stopX();
}

/* Sebastian Pietras */
void MobileEntity::setHp(int hp)
{
	if(hp > 100) hp = 100;
	else if(hp < 0) hp = 0;

	healthPoints_ = hp;
}

/* Sebastian Pietras */
bool MobileEntity::hurt(int damage)
{
	if(immunity_) return false;

	if(damage < 0) damage = 0;

	healthPoints_ -= damage;

	immunity_ = true;
	immunityClock_.restart();

	velocity_.y = speed_.y;
	onGround_ = false;

	if(healthPoints_ <= 0)
	{
		healthPoints_ = 0;
		return true;
	}

	return false;
}
