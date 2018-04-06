#pragma once
#include "Entity.h"

class Usable :
	public Entity
{
protected:
	bool canUse_;
	bool singleUse_;
public:
	Usable(sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f),
	       sf::Vector2f size = sf::Vector2f(100.0f, 100.0f), bool canUse = true, bool singleUse = false) :
		Entity(texture, position, size), canUse_(canUse), singleUse_(singleUse) {}

	bool use();
};
