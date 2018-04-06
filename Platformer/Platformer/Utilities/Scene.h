#pragma once
#include "../Entities/Player.h"
#include "Room.h"

class Scene
{
private:
	Player player_;
	Room currentRoom_;
	sf::View view_;
public:
	Scene(Player player, Room currentRoom);

	void update(float deltaTime, sf::RenderWindow& window);

	Player& getPlayer() const;
	Room& getRoom() const;

	void changeRoom(Room& room);
	bool isPlayerInBounds();

	void checkCollisions();
};
