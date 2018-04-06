#pragma once
#include "Scene.h"

class Game
{
private:
	Scene currentScene_;
	sf::RenderWindow window_;

	void Update(float deltaTime);
	bool HandleWindowEvents();
	void HandlePlayerControls();
	void Draw();
public:
	Game();

	bool Play();
};
