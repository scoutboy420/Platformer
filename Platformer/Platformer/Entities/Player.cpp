#include "Player.h"
#include "../Utilities/Resources.h"

void Player::update(const float deltaTime,
                    const sf::Vector2f playerPos,
                    const bool isPlayerVisible,
                    std::vector<Bullet>& bullets)
{
	MobileEntity::update(deltaTime, playerPos, isPlayerVisible, bullets);
	if(immunityClock_.getElapsedTime().asSeconds() >= 1.0f) immunity_ = false;
	if(!immunity_) immunityClock_.restart();
}

/* Sebastian Pietras */
void Player::onRoomChange(const std::string& roomName)
{
	MobileEntity::onRoomChange(roomName);

	Resources::getRoomJson(roomName).at("visited") = true;
}
