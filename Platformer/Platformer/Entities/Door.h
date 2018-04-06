#pragma once
#include "Usable.h"

class Door :
	public Usable
{
private:
	bool closed_;
	bool open();
public:
	Door(sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f),
	     sf::Vector2f size = sf::Vector2f(100.0f, 100.0f), bool canUse = true, bool closed = true) :
		Usable(texture, position, size, canUse, true), closed_(closed) {}

	bool use();
};
