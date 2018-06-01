#include "Enemy.h"
#include "Player.h"

void Enemy::onPlayerCollision(Player& player, const sf::Vector2f push)
{
	if(push.y > 0 && player.getVelocity().y < 0.0f)
	{
		player.jump(true);
		hurt(100000);
	}
	else player.hurt(damage_);
	if(player.isDashing()) hurt(player.getDashDamage());
}
