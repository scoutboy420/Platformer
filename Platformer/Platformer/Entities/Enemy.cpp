#include "Enemy.h"
/* Sebastian Pietras */
void Enemy::setHp(int hp)
{
	if(hp > 100) hp = 100;
	else if(hp < 0) hp = 0;

	healthPoints_ = hp;
}

/* Sebastian Pietras */
bool Enemy::hurt(int damage)
{
	if(damage < 0) damage = 0;

	healthPoints_ -= damage;

	if(healthPoints_ <= 0)
	{
		healthPoints_ = 0;
		return true;
	}

	return false;
}
