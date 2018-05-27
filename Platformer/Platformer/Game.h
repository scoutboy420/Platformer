#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "Entities/Player.h"
#include "Entities/Enemy.h"
#include "Entities/Entity.h"
#include "Entities/MobileEntity.h"
#include "Entities/Key.h"
#include "Utilities/Room.h"
#include "Utilities/Resources.h"
#include "Utilities/JSON/json.hpp"

class Game
{
	Player player_;
	std::vector<std::unique_ptr<Enemy>> enemies_;
	std::unordered_map<std::string, Room> loadedRooms_;
	sf::RenderWindow window_;
	sf::View view_;
	sf::Clock clock_; //to count time between frames
	sf::Text playerHealthText_;

	bool collides(const Entity& e1, const Entity& e2) const;
	sf::Vector2f checkPush(const MobileEntity& e1, const Entity& e2, float deltaTime) const;
	void checkCollisions(float deltaTime);
	void checkRoomChange(MobileEntity& entity);
	static void changeRoom(MobileEntity& entity, const std::string& roomName, int entranceId, sf::Vector2f offset);
	void checkCamera();
	void scaleView();
	void handleInput();
	bool handleWindowEvents();
	void update(float deltaTime);
	void draw();
	void showMiniMap();
	void save();

	/* Helpers */
	void checkBlockCollision(MobileEntity& mobile, const Entity& block, float deltaTime) const;
	void checkKeyCollision(const Player& player, Key& key) const;
	static bool isInsideView(const sf::FloatRect& viewRect, const Entity& entity);
	void drawEntities();
	void drawOverlay();
	void initializePlayer();
	static bool findTransportLocation(const MobileEntity& entity,
	                                  const Room& currentRoom,
	                                  Resources::direction dir,
	                                  const nlohmann::json& entrance,
	                                  std::string& roomName,
	                                  int& entranceId,
	                                  sf::Vector2f& offset);
	static sf::RectangleShape createRoomShape(const nlohmann::json& roomJson, float scale, float outlineThickness);
	sf::RectangleShape createMiniMapBackground(sf::Vector2f baseSize) const;
	void drawMiniMap(const sf::RectangleShape& background,
	                 sf::RectangleShape& currentRoomShape,
	                 std::vector<sf::RectangleShape>
	                 roomShapes,
	                 sf::Vector2f mapCenter);
	Room& getCurrentRoom();
	void setKeys();
public:
	Game(sf::VideoMode mode, const std::string& title);

	bool play();
};
