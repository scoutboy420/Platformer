#pragma once
#include "Entity.h"

class PhysicalEntity :
	public Entity
{
protected:
	sf::Vector2f velocity_;
	const float speed_, drag_, jumpSpeed_, gravity_;
	bool onGround_;
public:
	PhysicalEntity(sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f),
	               sf::Vector2f size = sf::Vector2f(100.0f, 100.0f), float speed = 10.0f, float drag = 50.0f,
	               float jumpSpeed = 30.0f, float gravity = 9.81f) :
		Entity(texture, position, size), speed_(speed), drag_(drag), jumpSpeed_(jumpSpeed), gravity_(gravity),
		onGround_(false) {}

	void update(float deltaTime);

	void moveHorizontal(float transform);
	void jump();

	/**
	 * \brief Checks how much object has to be pushed if colliding with other
	 * \param other Other entity that this entity is possibly colliding with
	 * \return Vector of how much this entity has to be pushed
	 */
	sf::Vector2f checkPush(const Entity& other) const;
};
