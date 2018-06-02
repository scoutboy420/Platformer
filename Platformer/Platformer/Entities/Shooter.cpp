#include "Shooter.h"
#include "../Utilities/Resources.h"

/* Sebastian Pietras */
void Shooter::update(const float deltaTime,
                     const sf::Vector2f playerPos,
                     const bool isPlayerVisible,
                     std::vector<Bullet>& bullets)
{
	if(!isActive) return;
	MobileEntity::update(deltaTime, playerPos, isPlayerVisible, bullets);
	//If player in visible, shoot at him every 2 seconds
	if(!isPlayerVisible || shootClock_.getElapsedTime().asSeconds() < 2.0f) return;

	bullets.push_back(Bullet(Resources::textures["bullet"], getCenter(), playerPos, 20, getCurrentRoomName()));

	shootClock_.restart();
}
