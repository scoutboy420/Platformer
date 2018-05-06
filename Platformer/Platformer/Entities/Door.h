#pragma once
#include "Entity.h"

class Door:
    public Entity
{
public:
    bool locked;

    Door(sf::Texture& texture, sf::Vector2f position) :
		Entity(texture, position), locked(true) { }

    Door();  //creates a key on the map
    ~Door();
};
