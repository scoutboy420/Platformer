#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
	try
	{
		Game game(sf::VideoMode(1280, 720), "Game");

		while(game.play()) {}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cin.ignore();
	}

	return 0;
}
