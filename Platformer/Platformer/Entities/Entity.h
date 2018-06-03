#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity
{
protected:
	sf::Sprite body_;
	sf::Vector2f size_;
	std::string currentRoomName_;
	bool tpImmunity_;
//	sf::Clock tpImmunity_;
public:
	virtual ~Entity() = default;
	bool isActive;

	Entity()
		: isActive(false) { }

	Entity(sf::Texture& texture, sf::Vector2f position, std::string roomName);

	const sf::Sprite& getBody() const { return body_; }
	sf::Vector2f getPosition() const { return body_.getPosition(); }
	sf::Vector2f getCenter() const;
	sf::Vector2f getSize() const { return size_; }
	std::string getCurrentRoomName() const { return currentRoomName_; }

	void setPosition(const sf::Vector2f position) { body_.setPosition(position); }
    //void changeRoom(const std::string& roomName) { currentRoomName_ = roomName;}

	virtual void onCollision(const Entity&, sf::Vector2f) {}
	virtual void onRoomChange(const std::string&) {}
	bool isTpImmune() const { return tpImmunity_; }
	virtual void setTpImmunity(bool a) { std::cout << "setTpImmunity from " << isTpImmune(); tpImmunity_ = a; std::cout << " to " << isTpImmune() << std::endl; }
//	bool isTpImmune() const override { return tpImmunity_.getElapsedTime().asSeconds() <= 2.00f; }
//	void restartTpImmunity() { tpImmunity_.restart(); }
};
