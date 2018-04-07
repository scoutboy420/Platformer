#include "Entity.h"

Entity::Entity(sf::Texture& texture, sf::Vector2f position)
{
	body_.setTexture(texture, true);
	body_.setPosition(position);
	size_ = body_.getTexture()->getSize();
	isActive_ = true;
}

sf::Vector2f Entity::getCenter() const
{
	float posX = getPosition().x;
	float posY = getPosition().y;
	float sizeX = getSize().x;
	float sizeY = getSize().y;

	return {posX + sizeX * 0.5f, posY + sizeY * 0.5f};
}

bool Entity::collides(const Entity& other) const
{
	//Distances
	float deltaX = other.getCenter().x - getCenter().x;
	float deltaY = other.getCenter().y - getCenter().y;
	//Intersections
	float intersectX = std::fabs(deltaX) - (other.getSize().x * 0.5f + getSize().x * 0.5f);
	float intersectY = std::fabs(deltaY) - (other.getSize().y * 0.5f + getSize().y * 0.5f);

	return intersectX < 0.0f && intersectY < 0.0f; //if both intersections are negative, then objects collide
}
