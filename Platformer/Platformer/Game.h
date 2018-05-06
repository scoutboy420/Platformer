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
	sf::Vector2f defaultViewSize_;

	void checkCollisions(float deltaTime);
	void checkRoomChange();
	void changeRoom(Resources::direction dir);
	void checkCamera();
	void scaleView();
	void handleInput();
	bool handleWindowEvents();
	void update(float deltaTime);
	void draw();
public:
	Game(sf::VideoMode mode, std::string title);

	bool play();
};
