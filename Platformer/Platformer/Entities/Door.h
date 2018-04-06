#pragma once
#include "Usable.h"
#include "Item.h"

class Door :
	public Usable
{
private:
	Item& key_;
	bool closed_;
public:
	Door(Item& key, sf::Texture texture, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f size = sf::Vector2f(100.0f, 100.0f), bool canUse = true, bool closed = true) :
		Usable(texture, position, size, canUse, true), key_(key), closed_(closed) {}

	void changeKey(Item& newKey);
	bool open(Item& key);
};
