#pragma once

/**
* @file
* @brief Abstract obstacle class
*/

#include "../Entity.h"
#include "../Player.h"

class Obstacle : public Entity
{
public:
	/**
	 * \brief Constructs an obstacles
	 * \param texture Texture
	 * \param position Position vector
	 * \param roomName Name of the room where the obstacle is
	 */
	Obstacle(sf::Texture& texture,
	         const sf::Vector2f position,
	         const std::string& roomName)
		: Entity(texture, position, roomName) { }

	virtual void update() {}
	virtual void onPlayerCollision(Player&) {}
};
