/** @cond */
#include <utility>
/** @endcond */
#include "Entity.h"

/* Sebastian Pietras */
Entity::Entity(sf::Texture& texture, const sf::Vector2f position, std::string roomName)
	: currentRoomName_(std::move(roomName))
{
	body_.setTexture(texture, true);
	body_.setPosition(position);
	size_ = sf::Vector2f(body_.getTexture()->getSize());
	isActive = true;
	tpImmunity_ = false;
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
