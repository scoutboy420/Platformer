#include "Laser.h"

void Laser::update()
{
	if(isActive && showClock_.getElapsedTime().asSeconds() > 1.0f)
	{
		isActive = false;
		showClock_.restart();
	}
	else if(!isActive && showClock_.getElapsedTime().asSeconds() > 2.0f)
	{
		isActive = true;
		showClock_.restart();
	}
}
