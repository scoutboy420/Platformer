#pragma once
#include "Entity.h"

/* Bernard Lesiewicz */
class Door : public Entity
{
	int id_;
public:
	Door(sf::Texture& texture, const sf::Vector2f position, const int id, const bool opened, const std::string& roomName)
		: Entity(texture, position, roomName)
		, id_(id) { isActive = !opened; }

	void open();
	int getId() const { return id_; }
};
