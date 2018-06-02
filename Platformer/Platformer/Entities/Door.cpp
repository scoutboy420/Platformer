#include "Door.h"
#include "../Utilities/Resources.h"

/* Sebastian Pietras */
void Door::open()
{
	isActive = false;
	Resources::getDoorJson(currentRoomName_, id_).at("opened") = true;
}
