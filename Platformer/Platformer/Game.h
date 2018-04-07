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
	sf::Clock clock_;

	void CheckCollisions();
	void handleInput();
	bool handleWindowEvents();
	void update(float deltaTime);
	void draw();
public:
	Game(sf::VideoMode mode, std::string title);

	bool play();
};
