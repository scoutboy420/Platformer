#pragma once
#include "Entity.h"

/* Bernard Lesiewicz */
class Door:
    public Entity
{
    int id_;
public:
    Door(sf::Texture& texture, sf::Vector2f position, int id) :
		Entity(texture, position), id_(id) { }
};
