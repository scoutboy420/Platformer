#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game(sf::VideoMode(1280, 720), "Game");

	while(game.play()) { }

	return 0;
}
