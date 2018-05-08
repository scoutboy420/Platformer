#pragma once
#include "Entity.h"
#include "Door.h"

class Key:
    public Entity
{
    int id_;
public:
    Key(sf::Texture& texture, sf::Vector2f position , int id) :
		Entity(texture, position), id_(id) { }

    const int getId() const {return id_;}
};
