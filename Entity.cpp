#include "Entity.h"

Entity::Entity(sf::Texture& texture, sf::Vector2f position)
{
	body_.setTexture(texture, true);
	body_.setPosition(position);
	size_ = sf::Vector2f(body_.getTexture()->getSize());
	isActive_ = true;
}

sf::Vector2f Entity::getCenter() const
{
	const float posX = getPosition().x;
	const float posY = getPosition().y;
	const float sizeX = getSize().x;
	const float sizeY = getSize().y;

	return {posX + sizeX * 0.5f, posY + sizeY * 0.5f};
}

bool Entity::collides(const Entity& other) const
{
	//Distances
	const float deltaX = other.getCenter().x - getCenter().x;
	const float deltaY = other.getCenter().y - getCenter().y;
	//Intersections
	const float intersectX = std::fabs(deltaX) - (other.getSize().x * 0.5f + getSize().x * 0.5f);
	const float intersectY = std::fabs(deltaY) - (other.getSize().y * 0.5f + getSize().y * 0.5f);

	return intersectX < 0.0f && intersectY < 0.0f; //if both intersections are negative, then objects collide
}
