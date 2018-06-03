#include "Player.h"
#include "../Utilities/Resources.h"

/* Sebastian Pietras */
void Player::dash()
{
	if(dashCooldown_.getElapsedTime().asSeconds() < 0.5f || mana_ < 10) return;

	if(movingRight_) velocity_.x = dashSpeed_;
	else velocity_.x = -dashSpeed_;

	mana_ -= 10;
	manaCooldown_.restart();

	dashClock_.restart();
	dashCooldown_.restart();
}

/* Sebastian Pietras */
void Player::shoot(std::vector<Bullet>& bullets)
{
	if(shootClock_.getElapsedTime().asSeconds() < 0.25f || mana_ < 5) return;

	sf::Vector2f target;
	if(movingRight_) target = {getCenter().x + 10.0f, getCenter().y};
	else target = {getCenter().x - 10.0f, getCenter().y};

	bullets.push_back(Bullet(Resources::textures["bullet"], getCenter(), target, 20, getCurrentRoomName()));

	mana_ -= 5;
	manaCooldown_.restart();

	shootClock_.restart();
}

/* Sebastian Pietras */
bool Player::hurt(const int damage, Player& p)
{
	const auto d = MobileEntity::hurt(damage, p);
	isActive = true;
	return d;
}

/* Sebastian Pietras */
void Player::heal(const int amount)
{
	if(amount <= 0) return;
	healthPoints_ += amount;
	if(healthPoints_ > 100) healthPoints_ = 100;
}

/* Sebastian Pietras */
void Player::addMana(const float amount)
{
	if(amount <= 0.0f) return;
	mana_ += amount;
	if(mana_ > 100.0f) mana_ = 100.0f;
}

/* Sebastian Pietras */
void Player::run(const bool runRight)
{
	if(isDashing()) return;

	movingRight_ = runRight;
	if(!runRight) velocity_.x = -speed_.x;
	else velocity_.x = speed_.x;
}

/* Sebastian Pietras */
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

	if(manaCooldown_.getElapsedTime().asSeconds() >= 2.5f) { addMana(deltaTime * 2.5f); }
}

/* Sebastian Pietras */
void Player::onRoomChange(const std::string& roomName)
{
	MobileEntity::onRoomChange(roomName);

	Resources::getRoomJson(roomName).at("visited") = true;
}
