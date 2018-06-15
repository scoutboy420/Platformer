#pragma once

/**
* @file
* @brief Portal class
*/

/** @cond */
#include <utility>
/** @endcond */
#include "../Entity.h"

/* Bernard Lesiewicz */
class Portal : public Entity
{
	int id_;
	int toId_;

	std::string toRoomName_;
	Portal* toPortal_;
public:

	/**
	 * \brief Constructs a portal
	 * \param texture Texture
	 * \param position Position vector
	 * \param roomName Name of the room where the portal is
	 * \param id ID of the portal
	 * \param toId ID of the target portal
	 * \param toRoomName Name of the room where the target portal is
	 */
	Portal(sf::Texture& texture,
	       const sf::Vector2f position,
	       const std::string& roomName,
	       const int id,
	       const int toId,
	       std::string toRoomName)
		: Entity(texture, position, roomName)
		, id_(id)
		, toId_(toId)
		, toRoomName_(std::move(toRoomName))
		, toPortal_(nullptr) {}

	void setToPortal(Portal* toPortal) { toPortal_ = toPortal; }

	std::string getToRoomName() const { return toRoomName_; }
	int getId() const { return id_; }
	int getToId() const { return toId_; }
	const Portal* getToPortal() const { return toPortal_; }
};
