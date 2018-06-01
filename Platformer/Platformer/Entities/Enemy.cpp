#include "Enemy.h"
#include "Player.h"

void Enemy::onPlayerCollision(Player& player, sf::Vector2f) const { player.hurt(damage_); }
