#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "Entities/Player.h"
#include "Entities/Enemies/Enemy.h"
#include "Entities/Entity.h"
#include "Entities/MobileEntity.h"
#include "Entities/Misc/Key.h"
#include "Utilities/Room.h"
#include "Utilities/Resources.h"
#include "Utilities/JSON/json.hpp"

class Game
{
	Player player_;
	std::vector<std::unique_ptr<Enemy>> enemies_;
	std::vector<Bullet> bullets_;
	std::vector<Bullet> playerBullets_;
	std::unordered_map<std::string, Room> loadedRooms_;
	sf::RenderWindow window_;
	std::vector<sf::Window*> errorWindows_;
	sf::View view_;
	sf::Clock clock_; //to count time between frames
	sf::Text playerHealthText_;
	sf::Text manaText_;

	bool collides(const Entity& e1, const Entity& e2) const;
	sf::Vector2f checkPush(const MobileEntity& e1, const Entity& e2, float deltaTime) const;
	void checkCollisions(float deltaTime);
	bool isInside(const Entity& e1, const Entity& e2) const;
	void checkPortals();
	void checkRoomChange(Entity& entity);
	static void teleport(Entity& entity, Portal& portal);
	static void changeRoom(Entity& entity, const std::string& roomName, int entranceId, sf::Vector2f offset);
	void checkCamera();
	void scaleView();
	void handleInput();
	bool handleWindowEvents();
	void update(float deltaTime);
	void draw();
	void showMiniMap();
	void save();
	void restart();

	/* Helpers */
	void checkBlockCollision(MobileEntity& mobile, const Entity& block, float deltaTime) const;
	void checkKeyCollision(const Player& player, Key& key) const;
	void checkEnemyCollision(Player& player, Enemy& enemy, float deltaTime) const;
	void checkObstaclesColllision();
	void checkBulletCollision();
	void checkPlayerInPortals();
	void checkEnemiesInPortals();
	void checkBulletsInPortals();
	void checkPlayerBulletCollision();
	bool isInsideView(const sf::FloatRect& viewRect, const Entity& entity) const;
	void drawEntities();
	void drawOverlay();
	void initializePlayer(bool def = false);
	static bool findTransportLocation(const Entity& entity,
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
	void setPortals();
	bool isRectangleInWay(const sf::FloatRect& rect, const sf::Vector2f& p1, const sf::Vector2f& p2) const;
	bool areInLine(const MobileEntity& e1, const MobileEntity& e2);
	void savePlayer() const;
	void saveEnemies();
	void showErrorWindow(const std::string& title, const std::string& message);
	void checkErrorWindows();
public:
	Game(sf::VideoMode mode, const std::string& title);

	bool play();
};
