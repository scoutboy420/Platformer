#pragma once
#include "Entity.h"

/* Bernard Lesiewicz */
class Key : public Entity
{
	int id_;
public:
	Key(sf::Texture& texture, const sf::Vector2f position, const int id)
		: Entity(texture, position)
		, id_(id) { }

	int getId() const { return id_; }
};
