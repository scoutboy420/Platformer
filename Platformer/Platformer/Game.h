#pragma once
#include "Entities/Player.h"
#include "Utilities/Room.h"

class Game
{
	Player player_;
	std::vector<bool> openedDoors_;
	Room currentRoom_;
	sf::RenderWindow window_;
	sf::View view_;
	sf::Clock clock_; //to count time between frames
	sf::Text playerHealthText_;

	void checkCollisions(float deltaTime);
	void checkRoomChange();
	void changeRoom(const std::string& roomName, int entranceId, sf::Vector2f offset);
	void checkCamera();
	void scaleView();
	void handleInput();
	bool handleWindowEvents();
	void update(float deltaTime);
	void draw();
	void showMiniMap();
	void save() const;

	/* Helpers */
	void checkBlockCollision(float deltaTime, const Entity& entity);
	static bool isInsideView(const sf::FloatRect& viewRect, const Entity& entity);
	void drawEntities();
	void drawOverlay();
	void initializePlayer();
	bool findTransportLocation(Resources::direction dir,
	                           const nlohmann::json& entrance,
		                       std::string& roomName,
	                           int& entranceId,
	                           sf::Vector2f& offset) const;
	static sf::RectangleShape createRoomShape(const nlohmann::json& roomJson, float scale, float outlineThickness);
	sf::RectangleShape createMiniMapBackground(sf::Vector2f baseSize) const;
	void drawMiniMap(const sf::RectangleShape& background,
	                 sf::RectangleShape& currentRoomShape,
	                 std::vector<sf::RectangleShape>
	                 roomShapes,
	                 sf::Vector2f mapCenter);
public:
	Game(sf::VideoMode mode, const std::string& title);

	bool play();
};
