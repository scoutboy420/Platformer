#include "Entity.h"

/* Sebastian Pietras */
Entity::Entity(sf::Texture& texture, const sf::Vector2f position)
{
	body_.setTexture(texture, true);
	body_.setPosition(position);
	size_ = sf::Vector2f(body_.getTexture()->getSize());
	isActive = true;
}

/* Sebastian Pietras */
sf::Vector2f Entity::getCenter() const
{
	const auto posX = getPosition().x;
	const auto posY = getPosition().y;
	const auto sizeX = getSize().x;
	const auto sizeY = getSize().y;

	return {posX + sizeX * 0.5f, posY + sizeY * 0.5f};
}

/* Sebastian Pietras */
bool Entity::collides(const Entity& other) const
{
	if(!isActive || !other.isActive) return false;

	//Distances
	const auto deltaX = other.getCenter().x - getCenter().x;
	const auto deltaY = other.getCenter().y - getCenter().y;
	//Intersections
	const auto intersectX = std::fabs(deltaX) - (other.getSize().x * 0.5f + getSize().x * 0.5f);
	const auto intersectY = std::fabs(deltaY) - (other.getSize().y * 0.5f + getSize().y * 0.5f);

	return intersectX < 0.0f && intersectY < 0.0f; //if both intersections are negative, then objects collide
}
