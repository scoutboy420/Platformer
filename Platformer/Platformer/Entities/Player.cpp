#include "Player.h"
#include "../Utilities/Resources.h"

void Player::dash()
{
	if(dashCooldown_.getElapsedTime().asSeconds() < 0.5f) return;

	if(movingRight_) velocity_.x = dashSpeed_;
	else velocity_.x = -dashSpeed_;

	dashClock_.restart();
	dashCooldown_.restart();
}

bool Player::hurt(const int damage)
{
	const auto d = MobileEntity::hurt(damage);
	isActive = true;
	return d;
}

void Player::run(const bool runRight)
{
	if(isDashing()) return;

	movingRight_ = runRight;
	if(!runRight) velocity_.x = -speed_.x;
	else velocity_.x = speed_.x;
}

void Player::update(const float deltaTime,
                    const sf::Vector2f playerPos,
                    const bool isPlayerVisible,
                    std::vector<Bullet>& bullets)
{
	if(!isActive) return;
	if(!isDashing()) MobileEntity::update(deltaTime, playerPos, isPlayerVisible, bullets);
	else
	{
		const auto transform = sf::Vector2f(velocity_.x * deltaTime, 0.0f);
		move(transform);
	}
}

/* Sebastian Pietras */
void Player::onRoomChange(const std::string& roomName)
{
	MobileEntity::onRoomChange(roomName);

	Resources::getRoomJson(roomName).at("visited") = true;
}
