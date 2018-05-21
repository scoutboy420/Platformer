#pragma once
#include "SFML/Graphics.hpp"

class Entity
{
protected:
	sf::Sprite body_;
	sf::Vector2f size_;

public:
	bool isActive;

	Entity()
		: isActive(false) { }

	Entity(sf::Texture& texture, sf::Vector2f position);

	const sf::Sprite& getBody() const { return body_; }
	sf::Vector2f getPosition() const { return body_.getPosition(); }
	sf::Vector2f getCenter() const;
	sf::Vector2f getSize() const { return size_; }

	bool collides(const Entity& other) const;
};
