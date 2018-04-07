#pragma once
#include "Entities/Player.h"
#include "Utilities/Room.h"

class Game
{
private:
	Player player_;
	Room currentRoom_;
	sf::RenderWindow window_;
	sf::View view_;
	sf::Clock clock_; //to count time between frames

	void checkCollisions();
	void handleInput();
	bool handleWindowEvents();
	void update(float deltaTime);
	void draw();
public:
	Game(sf::VideoMode mode, std::string title);

	bool play();
};
