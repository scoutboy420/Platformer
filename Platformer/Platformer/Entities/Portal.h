#pragma once
#include "Entity.h"
#include <utility>

/* Bernard Lesiewicz */
class Portal : public Entity
{
	int id_;
	int toId_;

	std::string toRoomName_;
	Portal* toPortal_;
public:

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
