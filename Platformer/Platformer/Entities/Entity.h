#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::RectangleShape body_;
	sf::Texture texture_;

	bool isActive_;
public:
	Entity(sf::Texture texture, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f size = sf::Vector2f(100.0f, 100.0f));

	const sf::RectangleShape& getBody() const { return body_; }
	const sf::Texture& getTexture() const { return texture_; }

	sf::Vector2f getPosition() const { return body_.getPosition(); }

	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setTexture(sf::Texture texture);

	void activate() { isActive_ = true; }
	void deactivate() { isActive_ = false; }

	bool collides(const Entity& other) const;
};

