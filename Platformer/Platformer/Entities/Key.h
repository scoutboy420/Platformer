#pragma once
#include "Entity.h"
#include "Door.h"

class Key:
    public Entity
{
public:
    bool collected;
    Door *door;
    Key(sf::Texture& texture, sf::Vector2f position, Door *door) :
		Entity(texture, position), collected(false), door(door) { }

    void collect();  //makes the door able to open, (++displays an icon on the screen (or menu/minimap))
};
