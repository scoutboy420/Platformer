#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::Sprite body_;
	sf::Vector2f size_;
	std::string currentRoomName_;
	bool tpImmunity_;
public:
	virtual ~Entity() = default;
	bool isActive;

	Entity()
		: tpImmunity_(false)
		, isActive(false) { }

	Entity(sf::Texture& texture, sf::Vector2f position, std::string roomName);

	const sf::Sprite& getBody() const { return body_; }
	sf::Vector2f getPosition() const { return body_.getPosition(); }
	sf::Vector2f getCenter() const;
	sf::Vector2f getSize() const { return size_; }
	std::string getCurrentRoomName() const { return currentRoomName_; }

	void setPosition(const sf::Vector2f position) { body_.setPosition(position); }

	virtual void onCollision(const Entity&, sf::Vector2f) {}
	virtual void onRoomChange(const std::string&) {}
	bool isTpImmune() const { return tpImmunity_; }
	virtual void setTpImmunity(const bool a) { tpImmunity_ = a; }
};
