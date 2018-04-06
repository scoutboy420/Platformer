#pragma once
#include "Scene.h"
#include "Map.h"

class Game
{
private:
	Scene currentScene_;
	sf::RenderWindow window_;

	void update(float deltaTime);
	bool handleWindowEvents();
	void handlePlayerControls();
	void draw();

	/**
	 * \brief Constructs new room and changes current room
	 * \param roomID ID of room in room matrix
	 */
	void changeRoom(sf::Vector2i roomID);
public:
	Game();

	/**
	 * \brief Main loop of game
	 * \return True if still playing
	 * \return False if closed
	 */
	bool play();
};
