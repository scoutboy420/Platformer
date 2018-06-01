#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(sf::Texture& texture,
               const sf::Vector2f position,
               const sf::Vector2f target,
               const int damage,
               const std::string& roomName)
	: Entity(texture, position, roomName)
	, damage_(damage)
{
	const auto line = target - position;
	const auto length = sqrtf(powf(line.x, 2) + powf(line.y, 2));
	velocity_ = 500.0f / length * line;
}

void Bullet::onPlayerCollision(Player& player) const { player.hurt(damage_); }
