#pragma once

/**
* @file
* @brief Key class
*/

/** @cond */
#include <utility>
/** @endcond */
#include "../Entity.h"
#include "Door.h"

/* Bernard Lesiewicz */
class Key : public Entity
{
	int doorId_;
	std::string doorRoomName_;
	Door* door_;
public:
	/**
	 * \brief Constructs a key
	 * \param texture Texture
	 * \param position Position vector
	 * \param doorId ID of the door this key opens
	 * \param doorRoomName Name of the door where the target door is
	 * \param pickedUp Is key picked up
	 * \param roomName Name of the room where the key is
	 */
	Key(sf::Texture& texture,
	    const sf::Vector2f position,
	    const int doorId,
	    std::string doorRoomName,
	    const bool pickedUp,
	    const std::string& roomName)
		: Entity(texture, position, roomName)
		, doorId_(doorId)
		, doorRoomName_(std::move(doorRoomName))
		, door_(nullptr) { isActive = !pickedUp; }

	int getDoorId() const { return doorId_; }
	std::string getDoorRoomName() const { return doorRoomName_; }
	const Door* getDoorPtr() const { return door_; }
	void setDoor(Door* door) { door_ = door; }

	void onCollision(const Entity&, sf::Vector2f) override;
};
