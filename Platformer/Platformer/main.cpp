#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game(sf::VideoMode(500, 500), "Game");

	while(game.play())
	{
	}

	return 0;
}
