#pragma once
#include "Entity.h"

/* Bernard Lesiewicz */
class Door : public Entity
{
	int id_;
public:
	Door(sf::Texture& texture, const sf::Vector2f position, const int id, const bool opened)
		: Entity(texture, position)
		, id_(id) { isActive = !opened; }

	void open() { isActive = false; }
	int getId() const { return id_; }
};
