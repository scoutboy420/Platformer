#pragma once

/**
* @file
* @brief Abstract enemy class
*/

#include "../MobileEntity.h"
#include "../../Utilities/Resources.h"

class Enemy : public MobileEntity
{
protected:
	int id_;
	int damage_;

public:
	Enemy()
		: id_(0)
		, damage_(0) {}

	/**
	 * \brief 
	 * \param texture Texture
	 * \param position Position vector
	 * \param speed Speed vector, where x is vertical speed and y is horizontal speed (jump speed)
	 * \param gravity Gravity value
	 * \param friction Friction value
	 * \param roomName Name of the room where the entity is
	 * \param hp Health points
	 * \param id ID of enemy
	 * \param damage Damage done by enemy to player by collision
	 */
	Enemy(sf::Texture& texture,
	      const sf::Vector2f position,
	      const sf::Vector2f speed,
	      const float gravity,
	      const float friction,
	      const std::string& roomName,
	      const int hp,
	      const int id,
	      const int damage)
		: MobileEntity(texture, position, speed, gravity, friction, roomName, hp)
		, id_(id)
		, damage_(damage) { }

	int getId() const { return id_; }

	bool hurt(int damage, Player&) override;
	bool isImmune() const override { return immunityClock_.getElapsedTime().asSeconds() <= 0.1f; }

	virtual void onPlayerCollision(Player& player, sf::Vector2f push);

	/**
	 * \brief Updates all data about the enemy to given json object
	 * \param enemyJson Reference to enemy json object (should be taken from Resources)
	 */
	virtual void saveData(nlohmann::json& enemyJson);
};
