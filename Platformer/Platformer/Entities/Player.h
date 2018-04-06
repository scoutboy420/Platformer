#pragma once
#include "PhysicalEntity.h"
#include "../Utilities/Equipment.h"
#include "Door.h"

class Player :
	public PhysicalEntity
{
private:
	Equipment eq_;
public:
	Player(sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f size = sf::Vector2f(100, 100),
	       float speed = 10.0f, float drag = 50.0f, float jumpSpeed = 30.0f, float gravity = 9.81f) :
		PhysicalEntity(texture, position, size, speed, drag, jumpSpeed, gravity) {}

	void pickUp(Item& item);
};
