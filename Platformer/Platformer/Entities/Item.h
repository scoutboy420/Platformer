#pragma once
#include "Usable.h"

class Item :
	public Usable
{
protected:
	bool equipped_;
public:
	Item(sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f),
	     sf::Vector2f size = sf::Vector2f(100.0f, 100.0f), bool canUse = true, bool singleUse = false,
	     bool equipped = false) :
		Usable(texture, position, size, canUse, singleUse), equipped_(equipped) {}

	bool pickUp();
	bool use();
};
