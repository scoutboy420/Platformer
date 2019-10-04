#pragma once

/**
* @file
* @brief Door class
*/

#include "../Entity.h"

/* Bernard Lesiewicz */
class Door : public Entity
{
	int id_;
public:
	/**
	 * \brief Constructs a door
	 * \param texture Texture
	 * \param position Position vector
	 * \param id ID of the door
	 * \param opened Is the door opened
	 * \param roomName Name of the room where the door is
	 */
	Door(sf::Texture& texture,
	     const sf::Vector2f position,
	     const int id,
	     const bool opened,
	     const std::string& roomName)
		: Entity(texture, position, roomName)
		, id_(id) { isActive = !opened; }

	void open();
	int getId() const { return id_; }
};
