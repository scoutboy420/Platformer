#include "Flier.h"

void Flier::update(const float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&)
{
	if(!isActive) return;

	updateText();

	//Movement in random direction every 0.75 seconds
	if(movingClock_.getElapsedTime().asSeconds() >= 0.75f)
	{
		velocity_.x = float(dist_(e2_)) * 30.0f;
		velocity_.y = float(dist_(e2_)) * 30.0f;

		movingClock_.restart();
	}

	velocity_.x *= 1.0f / (1.0f + deltaTime * friction_);
	velocity_.y *= 1.0f / (1.0f + deltaTime * friction_);

	if(std::fabs(velocity_.x) < 0.0001f) velocity_.x = 0.0f;
	if(std::fabs(velocity_.y) < 0.0001f) velocity_.y = 0.0f;

	const auto transform = sf::Vector2f(velocity_.x * deltaTime, velocity_.y * deltaTime);
	move(transform);
}
