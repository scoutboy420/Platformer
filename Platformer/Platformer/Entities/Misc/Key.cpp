#include "Key.h"
#include "../../Utilities/Resources.h"

/* Sebastian Pietras */
void Key::onCollision(const Entity&, sf::Vector2f)
{
	isActive = false;
	Resources::getKeyJson(getCurrentRoomName(), doorId_).at("pickedUp") = true;
	door_->open();
}
