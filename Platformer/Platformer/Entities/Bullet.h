#pragma once

/**
* @file
* @brief Bullet class
*/

#include "Entity.h"

class Player;
class Enemy;

class Bullet : public Entity
{
	sf::Vector2f velocity_;
	int damage_;
public:
	/**
	 * \brief Constructs a bullet
	 * \param texture Texture
	 * \param position Position vector
	 * \param target Target position vector (where should the bullet fly)
	 * \param damage Damage done by bullet
	 * \param roomName Name of the room where the bullet is
	 */
	Bullet(sf::Texture& texture,
	       sf::Vector2f position,
	       sf::Vector2f target,
	       int damage,
	       const std::string& roomName);

	void update(const float deltaTime) { body_.move(velocity_ * deltaTime); }

	void onPlayerCollision(Player& player) const;
	void onEnemyCollision(Enemy& enemy, Player& player) const;
	void onRoomChange(const std::string& roomName) override { currentRoomName_ = roomName; }
};
