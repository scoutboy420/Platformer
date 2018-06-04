#include "Enemy.h"
#include "../Player.h"

/* Sebastian Pietras */
bool Enemy::hurt(const int damage, Player& p)
{
	const auto dead = MobileEntity::hurt(damage, p);
	if(dead)
	{
		p.heal(damage_);
		p.addMana(float(damage_));
	}
	return dead;
}

/* Sebastian Pietras */
void Enemy::onPlayerCollision(Player& player, const sf::Vector2f push)
{
	if(push.y > 0 && player.getVelocity().y < 0.0f)
	{
		player.jump(true);
		hurt(100000, player);
	}
	else player.hurt(damage_, player);
	if(player.isDashing()) hurt(player.getDashDamage(), player);
}

/* Sebastian Pietras */
void Enemy::saveData(json& enemyJson)
{
	enemyJson.at("positionX") = getPosition().x;
	enemyJson.at("positionY") = getPosition().y;
	enemyJson.at("room") = getCurrentRoomName();
	enemyJson.at("hp") = getHp();
}
