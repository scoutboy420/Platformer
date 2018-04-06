#pragma once
#include "Door.h"
#include "Item.h"

class Key :
	Item
{
private:
	Door& door_;
	void openDoor();
public:
	Key(Door& door, sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f),
	    sf::Vector2f size = sf::Vector2f(100.0f, 100.0f), bool canUse = true, bool singleUse = false,
	    bool equipped = false) :
		Item(texture, position, size, canUse, singleUse, equipped), door_(door) {}

	bool use();
};
