#include "MobileEntity.h"
#include "../Utilities/Resources.h"

void MobileEntity::updateText()
{
	healthText_.setString(std::to_string(healthPoints_));
	const auto width = healthText_.getGlobalBounds().width, height = healthText_.getGlobalBounds().height;
	const auto xPos = getCenter().x - width * 0.5f, yPos = getPosition().y - height - 10.0f;
	healthText_.setPosition(xPos, yPos);
}

MobileEntity::MobileEntity(sf::Texture& texture,
                           const sf::Vector2f position,
                           const sf::Vector2f speed,
                           const float gravity,
                           const float friction,
                           const std::string& roomName,
                           const int hp)
	: Entity(texture, position, roomName)
	, velocity_(0.0f, 0.0f)
	, speed_(speed)
	, gravity_(gravity)
	, friction_(friction)
	, onGround_(false)
	, healthPoints_(hp)
{
	healthText_.setFont(Resources::fonts["vcr"]);
	healthText_.setFillColor(sf::Color::White);
	healthText_.setOutlineColor(sf::Color::Black);
	healthText_.setOutlineThickness(1.0f);
	healthText_.setCharacterSize(20);
}

/* Sebastian Pietras, Bernard Lesiewicz */
void MobileEntity::update(const float deltaTime, sf::Vector2f, bool, std::vector<Bullet>&)
{
	if(!isActive) return;

	updateText();

	velocity_.y -= gravity_ * deltaTime;

	velocity_.x *= 1.0f / (1.0f + deltaTime * friction_);

	if(std::fabs(velocity_.x) < 0.0001f) velocity_.x = 0.0f;

	const auto transform = sf::Vector2f(velocity_.x * deltaTime, velocity_.y * deltaTime);
	move(transform);
}

/* Sebastian Pietras */
void MobileEntity::jump(const bool force)
{
	if(onGround_ || force)
	{
		velocity_.y = speed_.y;
		onGround_ = false;
	}
}

/* Sebastian Pietras */
void MobileEntity::onCollision(const Entity&, const sf::Vector2f push)
{
	if(push.y > 0) //if it pushes the entity upwards, then the entity is on top of something
	{
		onGround_ = true;
	}
	if(fabs(push.y) > 0) stopY();
	if(fabs(push.x) > 0) stopX();
}

/* Sebastian Pietras */
void MobileEntity::setHp(int hp)
{
	if(hp > 100) hp = 100;
	else if(hp < 0) hp = 0;

	healthPoints_ = hp;
}

/* Sebastian Pietras */
bool MobileEntity::hurt(int damage)
{
	if(isImmune()) return false;

	if(damage < 0) damage = 0;

	healthPoints_ -= damage;

	immunityClock_.restart();

	jump(true);

	if(healthPoints_ <= 0)
	{
		healthPoints_ = 0;
		isActive = false;
		return true;
	}

	return false;
}
