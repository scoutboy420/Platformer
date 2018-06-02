#include "Game.h"

/* Sebastian Pietras */
bool Game::isRectangleInWay(const sf::FloatRect& rect, const sf::Vector2f& p1, const sf::Vector2f& p2) const
{
	// Find min and max X for the segment
	auto minX = std::min(p1.x, p2.x);
	auto maxX = std::max(p1.x, p2.x);

	// Find the intersection of the segment's and rectangle's x-projections
	if(maxX > rect.left + rect.width) maxX = rect.left + rect.width;

	if(minX < rect.left) minX = rect.left;

	// If Y-projections do not intersect then there's no intersection
	if(minX > maxX) return false;

	// Find corresponding min and max Y for min and max X we found before
	auto minY = p1.y;
	auto maxY = p2.y;

	const auto dx = p2.x - p1.x;
	if(std::abs(dx) > 0.0001f)
	{
		const auto k = (p2.y - p1.y) / dx;
		const auto b = p1.y - k * p1.x;
		minY = k * minX + b;
		maxY = k * maxX + b;
	}

	if(minY > maxY) std::swap(minY, maxY);

	// Find the intersection of the segment's and rectangle's y-projections
	if(maxY > rect.top + rect.height) maxY = rect.top + rect.height;

	if(minY < rect.top) minY = rect.top;

	// If Y-projections do not intersect then there's no intersection
	return minY <= maxY;
}

/* Sebastian Pietras */
bool Game::areInLine(const MobileEntity& e1, const MobileEntity& e2)
{
	if(e1.getCurrentRoomName() != e2.getCurrentRoomName()) return false;
	if(!e1.isActive || !e2.isActive) return false;

	auto lined = true;

	for(auto& block : loadedRooms_[e1.getCurrentRoomName()].getEntities())
	{
		if(!block.isActive) continue;
		if(isRectangleInWay(block.getBody().getGlobalBounds(), e1.getCenter(), e2.getCenter()))
		{
			lined = false;
			break;
		}
	}
	for(auto& door : loadedRooms_[e1.getCurrentRoomName()].getDoors())
	{
		if(!door.isActive) continue;
		if(isRectangleInWay(door.getBody().getGlobalBounds(), e1.getCenter(), e2.getCenter()))
		{
			lined = false;
			break;
		}
	}

	return lined;
}

/* Sebastian Pietras */
bool Game::collides(const Entity& e1, const Entity& e2) const
{
	if(!e1.isActive || !e2.isActive) return false;

	//Distances
	const auto deltaX = e2.getCenter().x - e1.getCenter().x;
	const auto deltaY = e2.getCenter().y - e1.getCenter().y;
	//Intersections
	const auto intersectX = std::fabs(deltaX) - (e2.getSize().x * 0.5f + e1.getSize().x * 0.5f);
	const auto intersectY = std::fabs(deltaY) - (e2.getSize().y * 0.5f + e1.getSize().y * 0.5f);

	return intersectX < 0.0f && intersectY < 0.0f; //if both intersections are negative, then objects collide
}

/* Sebastian Pietras, Bernard Lesiewicz */
sf::Vector2f Game::checkPush(const MobileEntity& e1, const Entity& e2, const float deltaTime) const
{
	if(!e1.isActive || !e2.isActive) return {0.0f, 0.0f};
	const auto deltaX = e2.getCenter().x - e1.getCenter().x;
	const auto deltaY = e2.getCenter().y - e1.getCenter().y;
	const auto intersectX = std::fabs(deltaX) - (e2.getSize().x * 0.5f + e1.getSize().x * 0.5f);
	const auto intersectY = std::fabs(deltaY) - (e2.getSize().y * 0.5f + e1.getSize().y * 0.5f);

	if(intersectX < 0.0f && intersectY < 0.0f &&
		(intersectX <= -fabs(deltaTime * e1.getVelocity().x) - 0.001f ||
			intersectY <= -fabs(deltaTime * e1.getVelocity().y) - 0.001f))
	{
		if(intersectX > intersectY)
		{
			if(deltaX > 0.0f) return {intersectX, 0.0f};
			return {-intersectX, 0.0f};
		}
		if(intersectX < intersectY)
		{
			if(deltaY > 0.0f) return {0.0f, -intersectY};
			return {0.0f, intersectY};
		}

		return {intersectX, -intersectY};
	}

	return {0.0f, 0.0f};
}

/* Sebastian Pietras */
void Game::checkBlockCollision(MobileEntity& mobile, const Entity& block, const float deltaTime) const
{
	if(collides(mobile, block))
	{
		const auto push = checkPush(mobile, block, deltaTime);
		mobile.move(push);
		mobile.onCollision(block, push);
	}
}

/* Sebastian Pietras */
void Game::checkKeyCollision(const Player& player, Key& key) const
{
	if(collides(player, key)) { key.onCollision(player, sf::Vector2f(0, 0)); }
}

/* Sebastian Pietras */
void Game::checkEnemyCollision(Player& player, Enemy& enemy, const float deltaTime) const
{
	if(collides(player, enemy)) { enemy.onPlayerCollision(player, checkPush(player, enemy, deltaTime)); }
}

/* Sebastian Pietras */
void Game::checkBulletCollision()
{
	for(auto it = bullets_.begin(); it != bullets_.end();)
	{
		auto deleted = false;
		for(auto& block : loadedRooms_[it->getCurrentRoomName()].getEntities())
		{
			if(collides(*it, block))
			{
				deleted = true;
				break;
			}
		}
		for(auto& door : loadedRooms_[it->getCurrentRoomName()].getDoors())
		{
			if(collides(*it, door))
			{
				deleted = true;
				break;
			}
		}
		if(deleted) it = bullets_.erase(it);
		else ++it;
	}

	for(auto it = bullets_.begin(); it != bullets_.end();)
	{
		if(it->getCurrentRoomName() == player_.getCurrentRoomName())
		{
			if(collides(*it, player_))
			{
				it->onPlayerCollision(player_);
				it = bullets_.erase(it);
			}
			else ++it;
		}
		else ++it;
	}
}

/* Sebastian Pietras */
void Game::checkPlayerBulletCollision()
{
	for(auto it = playerBullets_.begin(); it != playerBullets_.end();)
	{
		auto deleted = false;
		for(auto& block : loadedRooms_[it->getCurrentRoomName()].getEntities())
		{
			if(collides(*it, block))
			{
				deleted = true;
				break;
			}
		}
		for(auto& door : loadedRooms_[it->getCurrentRoomName()].getDoors())
		{
			if(collides(*it, door))
			{
				deleted = true;
				break;
			}
		}
		if(deleted) it = playerBullets_.erase(it);
		else ++it;
	}

	for(auto& enemy : enemies_)
	{
		for(auto it = playerBullets_.begin(); it != playerBullets_.end();)
		{
			if(it->getCurrentRoomName() == enemy->getCurrentRoomName())
			{
				if(collides(*it, *enemy))
				{
					it->onEnemyCollision(*enemy, player_);
					it = playerBullets_.erase(it);
				}
				else ++it;
			}
			else ++it;
		}
	}
}


/* Sebastian Pietras, Bernard Lesiewicz*/
void Game::checkCollisions(const float deltaTime)
{
	auto& playerRoom = getCurrentRoom();
	for(const auto& entity : playerRoom.getEntities()) checkBlockCollision(player_, entity, deltaTime);
	for(const auto& door : playerRoom.getDoors()) checkBlockCollision(player_, door, deltaTime);
	for(auto& key : playerRoom.getKeys()) checkKeyCollision(player_, key);

	for(auto& enemy : enemies_)
	{
		auto& enemyRoom = loadedRooms_[enemy->getCurrentRoomName()];
		for(const auto& entity : enemyRoom.getEntities()) checkBlockCollision(*enemy, entity, deltaTime);
		for(const auto& door : enemyRoom.getDoors()) checkBlockCollision(*enemy, door, deltaTime);

		if(&enemyRoom == &playerRoom) checkEnemyCollision(player_, *enemy, deltaTime);
	}

	checkBulletCollision();
	checkPlayerBulletCollision();
}

/* Sebastian Pietras */
bool Game::findTransportLocation(const Entity& entity,
                                 const Room& currentRoom,
                                 const Resources::direction dir,
                                 const nlohmann::json& entrance,
                                 std::string& roomName,
                                 int& entranceId,
                                 sf::Vector2f& offset)
{
	switch(dir)
	{
	case Resources::direction::LEFT: if(entity.getCenter().y >= entrance.at("y").get<float>() &&
			entity.getCenter().y <= entrance.at("y").get<float>() + entrance.at("height").get<float>() * 50.0f)
		{
			if(entrance.at("x").get<float>() == 0.0f)
			{
				roomName = entrance.at("to").at("roomName").get<std::string>();
				entranceId = entrance.at("to").at("entranceID").get<int>();
				offset = sf::Vector2f(-entity.getSize().x * 0.5f + 50.0f, entity.getPosition().y - entrance.at("y").get<float>());
				return true;
			}
		}
		break;
	case Resources::direction::RIGHT: if(entity.getCenter().y >= entrance.at("y").get<float>() &&
			entity.getCenter().y <= entrance.at("y").get<float>() + entrance.at("height").get<float>() * 50.0f)
		{
			if(entrance.at("x").get<float>() + 50.0f == currentRoom.getSize().x)
			{
				roomName = entrance.at("to").at("roomName").get<std::string>();
				entranceId = entrance.at("to").at("entranceID").get<int>();
				offset = sf::Vector2f(-entity.getSize().x * 0.5f, entity.getPosition().y - entrance.at("y").get<float>());
				return true;
			}
		}
		break;
	case Resources::direction::UP: if(entity.getCenter().x >= entrance.at("x").get<float>() &&
			entity.getCenter().x <= entrance.at("x").get<float>() + entrance.at("width").get<float>() * 50.0f)
		{
			if(entrance.at("y").get<float>() == 0.0f)
			{
				roomName = entrance.at("to").at("roomName").get<std::string>();
				entranceId = entrance.at("to").at("entranceID").get<int>();
				offset = sf::Vector2f(entity.getPosition().x - entrance.at("x").get<float>(), -entity.getSize().y * 0.5f + 50.0f);
				return true;
			}
		}
		break;
	case Resources::direction::DOWN: if(entity.getCenter().x >= entrance.at("x").get<float>() &&
			entity.getCenter().x <= entrance.at("x").get<float>() + entrance.at("width").get<float>() * 50.0f)
		{
			if(entrance.at("y").get<float>() + 50.0f == currentRoom.getSize().y)
			{
				roomName = entrance.at("to").at("roomName").get<std::string>();
				entranceId = entrance.at("to").at("entranceID").get<int>();
				offset = sf::Vector2f(entity.getPosition().x - entrance.at("x").get<float>(), -entity.getSize().y * 0.5f);
				return true;
			}
		}
		break;
	}

	return false;
}

/* Sebastian Pietras */
void Game::checkRoomChange(Entity& entity)
{
	if(!entity.isActive) return;

	auto& currentRoom = loadedRooms_[entity.getCurrentRoomName()];

	Resources::direction dir;
	if(entity.getCenter().x < 0.0f) dir = Resources::direction::LEFT;
	else if(entity.getCenter().x > currentRoom.getSize().x) dir = Resources::direction::RIGHT;
	else if(entity.getCenter().y < 0.0f) dir = Resources::direction::UP;
	else if(entity.getCenter().y > currentRoom.getSize().y) dir = Resources::direction::DOWN;
	else return;

	//Messy and assumes blocks are 50x50 but works

	std::string roomName;
	auto entranceId = 0;
	sf::Vector2f offset = {0.0f, 0.0f};

	//Find which entrance this entrance leads to and entity position relative to this entrance
	for(const auto& entrance : json(Resources::getRoomJson(entity.getCurrentRoomName()).at("entrances")))
	{
		if(findTransportLocation(entity, currentRoom, dir, entrance, roomName, entranceId, offset)) break;
	}

	if(roomName.empty()) throw std::runtime_error("Target room not found.\nCurrent room: " + entity.getCurrentRoomName() +
	                                              "\nEntity position: " + std::to_string(entity.getPosition().x) + "," +
	                                              std::to_string(entity.getPosition().y));

	changeRoom(entity, roomName, entranceId, offset);
}

/* Sebastian Pietras */
void Game::changeRoom(Entity& entity,
                      const std::string& roomName,
                      const int entranceId,
                      const sf::Vector2f offset)
{
	sf::Vector2f entrancePos = {0.0f, 0.0f};

	for(const auto& entrances : json(Resources::getRoomJson(roomName).at("entrances")))
	{
		if(entrances.at("id").get<int>() == entranceId)
		{
			entrancePos = sf::Vector2f(entrances.at("x").get<float>(), entrances.at("y").get<float>());
			break;
		}
	}

	entity.setPosition(entrancePos + offset); //Apply offset so movement can be smooth
	entity.onRoomChange(roomName);
}

/* Sebastian Pietras */
void Game::checkCamera()
{
	auto camX = player_.getCenter().x, camY = player_.getCenter().y;
	const auto& currentRoom = getCurrentRoom();

	//Bound camera if it goes outside walls (assuming room is rectangular)
	if(camX - view_.getSize().x * 0.5f < 0.0f) camX += view_.getSize().x * 0.5f - camX;

	if(camX + view_.getSize().x * 0.5f > currentRoom.getSize().x)
		camX -= camX + view_.getSize().x * 0.5f - currentRoom
		                                          .getSize().x;

	if(camY - view_.getSize().y * 0.5f < 0.0f) camY += view_.getSize().y * 0.5f - camY;

	if(camY + view_.getSize().y * 0.5f > currentRoom.getSize().y)
		camY -= camY + view_.getSize().y * 0.5f - currentRoom
		                                          .getSize().y;

	view_.setCenter(camX, camY);
}

/* Sebastian Pietras */
void Game::scaleView()
{
	view_.setSize(sf::Vector2f(window_.getSize()));
	//If current view is bigger than entire room, scale it down to fit entire room (and no more)

	const auto ratioX = getCurrentRoom().getSize().x / view_.getSize().x,
	           ratioY = getCurrentRoom().getSize().y / view_.getSize().y;
	const auto dominatingRatio = std::min(ratioX, ratioY);

	if(dominatingRatio < 1.0f) view_.zoom(dominatingRatio);
}

/* Sebastian Pietras */
void Game::handleInput()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player_.run(true);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player_.run(false);

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) player_.dash();

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) player_.shoot(playerBullets_);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) player_.jump(false);
}

/* Sebastian Pietras */
void Game::savePlayer() const
{
	Resources::playerData.at("positionX") = player_.getPosition().x;
	Resources::playerData.at("positionY") = player_.getPosition().y;
	Resources::playerData.at("startingRoom") = player_.getCurrentRoomName();
	Resources::playerData.at("hp") = player_.getHp();
	Resources::playerData.at("mana") = player_.getMana();
}

/* Sebastian Pietras */
void Game::saveEnemies()
{
	for(auto& enemy : enemies_)
	{
		auto& enemyJson = Resources::getEnemyJson(enemy->getId());
		enemy->saveData(enemyJson);
	}
}

/* Sebastian Pietras */
void Game::showErrorWindow(const std::string& title, const std::string& message)
{
	auto errorText = sf::Text(message, Resources::fonts["roboto"]);
	errorText.setCharacterSize(22);
	errorText.setFillColor(sf::Color::Black);

	const auto width = unsigned(errorText.getGlobalBounds().width) * 2, height =
			           unsigned(errorText.getGlobalBounds().height) * 4;
	auto errorWindow = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

	errorWindow->clear(sf::Color::White);

	errorText.setPosition(0.25f * width, 3.0f / 8.0f * height);
	errorWindow->draw(errorText);
	errorWindow->display();

	errorWindows_.push_back(errorWindow);
}

void Game::checkErrorWindows()
{
	sf::Event e{};
	for(auto it = errorWindows_.begin(); it != errorWindows_.end();)
	{
		auto close = false;
		while(!close && (*it)->pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
			{
				(*it)->close();
				delete *it;
				it = errorWindows_.erase(it);
				close = true;
			}
		}

		if(!close) ++it;
	}
}

/* Sebastian Pietras */
void Game::save()
{
	savePlayer();
	saveEnemies();
	Resources::save();
}

void Game::restart()
{
	loadedRooms_ = Resources::createRooms(true);
	setKeys();
	enemies_ = Resources::createEnemies(true);

	initializePlayer(true);

	view_ = sf::View(player_.getCenter(), sf::Vector2f(window_.getSize()));

	scaleView();

	window_.setView(view_);
}

/* Sebastian Pietras */
bool Game::handleWindowEvents()
{
	sf::Event e{};

	while(window_.pollEvent(e))
	{
		switch(e.type)
		{
		case sf::Event::Closed: try { save(); }
			catch(const std::exception& ex)
			{
				showErrorWindow("Error", "Can't save.\n" + std::string(ex.what()));
				return true;
			}
			window_.close();
			return false;
		case sf::Event::Resized: scaleView();
		default: break;
		}
	}

	return true;
}

/* Sebastian Pietras */
void Game::update(const float deltaTime)
{
	player_.update(deltaTime, player_.getPosition(), true, bullets_);
	for(auto& enemy : enemies_) enemy->update(deltaTime, player_.getCenter(), areInLine(player_, *enemy), bullets_);
	for(auto& bullet : bullets_) bullet.update(deltaTime);
	for(auto& bullet : playerBullets_) bullet.update(deltaTime);

	checkCollisions(deltaTime);

	try { checkRoomChange(player_); }
	catch(const std::exception& e)
	{
		showErrorWindow("Error", "Player can't change room.\n" + std::string(e.what()));
		restart();
	}

	scaleView();
	try
	{
		for(auto& enemy : enemies_) checkRoomChange(*enemy);
		for(auto& bullet : bullets_) checkRoomChange(bullet);
		for(auto& bullet : playerBullets_) checkRoomChange(bullet);
	}
	catch(const std::exception& e)
	{
		showErrorWindow("Error", "Entity can't change room.\n" + std::string(e.what()));
		restart();
	}

	checkCamera();
}

/* Sebastian Pietras */
bool Game::isInsideView(const sf::FloatRect& viewRect, const Entity& entity) const
{
	if(!entity.isActive || entity.getCurrentRoomName() != player_.getCurrentRoomName()) return false;
	const auto entityRect = entity.getBody().getGlobalBounds();
	return viewRect.intersects(entityRect);
}

/* Sebastian Pietras */
void Game::drawEntities()
{
	const auto viewRect = sf::FloatRect(view_.getCenter() - sf::Vector2f(view_.getSize().x * 0.5f,
	                                                                     view_.getSize().y * 0.5f),
	                                    view_.getSize());

	for(const auto& entity : getCurrentRoom().getEntities())
		if(isInsideView(viewRect, entity))
			window_.
					draw(entity.getBody());

	for(const auto& door : getCurrentRoom().getDoors()) if(isInsideView(viewRect, door)) window_.draw(door.getBody());

	for(const auto& key : getCurrentRoom().getKeys()) if(isInsideView(viewRect, key)) window_.draw(key.getBody());

	for(auto& enemy : enemies_)
	{
		if(isInsideView(viewRect, *enemy))
		{
			window_.draw(enemy->getBody());
			window_.draw(enemy->getHealthText());
		}
	}

	for(auto& bullet : bullets_) if(isInsideView(viewRect, bullet)) window_.draw(bullet.getBody());
	for(auto& bullet : playerBullets_) if(isInsideView(viewRect, bullet)) window_.draw(bullet.getBody());

	window_.draw(player_.getBody());
}

/* Sebastian Pietras */
void Game::drawOverlay()
{
	for(auto e : getCurrentRoom().getGradientEdges()) window_.draw(e.data(), 4, sf::Quads);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)) showMiniMap();

	window_.setView(sf::View(sf::Vector2f(window_.getSize()) * 0.5f,
	                         sf::Vector2f(window_.getSize())));

	playerHealthText_.setString(std::to_string(player_.getHp()));
	manaText_.setString(std::to_string(int(player_.getMana())));
	window_.draw(playerHealthText_);
	window_.draw(manaText_);
}

/* Sebastian Pietras, Bernard Lesiewicz */
void Game::draw()
{
	window_.clear(sf::Color::Black);
	window_.setView(view_);
	window_.draw(getCurrentRoom().getBackground());

	drawEntities();
	drawOverlay();

	window_.display();
}

/* Sebastian Pietras */
sf::RectangleShape Game::createRoomShape(const nlohmann::json& roomJson,
                                         const float scale,
                                         const float outlineThickness)
{
	auto shape = sf::RectangleShape(sf::Vector2f(roomJson.at("width").get<float>() * scale -
	                                             outlineThickness,
	                                             roomJson.at("height").get<float>() * scale -
	                                             outlineThickness));
	shape.setPosition(roomJson.at("globalX").get<float>() / 50.0f * scale,
	                  roomJson.at("globalY").get<float>() / 50.0f * scale);

	const auto r = roomJson.at("colorR").get<int>();
	const auto g = roomJson.at("colorG").get<int>();
	const auto b = roomJson.at("colorB").get<int>();

	shape.setFillColor(sf::Color(r, g, b));

	shape.setOutlineColor(sf::Color::Blue);
	shape.setOutlineThickness(outlineThickness);

	return shape;
}

/* Sebastian Pietras */
sf::RectangleShape Game::createMiniMapBackground(const sf::Vector2f baseSize) const
{
	auto background = sf::RectangleShape(sf::Vector2f(baseSize.x * 1.25f, baseSize.y * 1.25f));
	background.setPosition(sf::Vector2f(window_.getSize().x * 0.5f, window_.getSize().y * 0.5f) -
	                       sf::Vector2f(background.getSize().x * 0.5f, background.getSize().y * 0.5f));
	background.setFillColor(sf::Color::Black);

	return background;
}

/* Sebastian Pietras */
void Game::drawMiniMap(const sf::RectangleShape& background,
                       sf::RectangleShape& currentRoomShape,
                       std::vector<sf::RectangleShape> roomShapes,
                       const sf::Vector2f mapCenter)
{
	//Draw minimap independently of current view
	window_.setView(sf::View(sf::Vector2f(window_.getSize().x * 0.5f, window_.getSize().y * 0.5f),
	                         sf::Vector2f(window_.getSize())));

	window_.draw(background);

	for(auto shape : roomShapes)
	{
		//Transform from local to global position
		shape.setPosition(sf::Vector2f(window_.getSize().x * 0.5f, window_.getSize().y * 0.5f) - mapCenter +
		                  shape.getPosition());
		window_.draw(shape);
	}

	currentRoomShape.setPosition(sf::Vector2f(window_.getSize().x * 0.5f, window_.getSize().y * 0.5f) - mapCenter +
	                             currentRoomShape.getPosition());
	window_.draw(currentRoomShape);
}

/* Sebastian Pietras */
Room& Game::getCurrentRoom()
{
	const auto roomName = player_.getCurrentRoomName();

	return loadedRooms_[roomName];
}

/* Sebastian Pietras */
void Game::showMiniMap()
{
	std::vector<sf::RectangleShape> roomShapes;
	sf::RectangleShape currentRoomShape;
	auto upperLeft = sf::Vector2f(0.0f, 0.0f), lowerRight = sf::Vector2f(0.0f, 0.0f);

	const auto outlineThickness = 2.0f;
	const auto scale = std::min(float(window_.getSize().x), float(window_.getSize().y)) / 50.0f;

	for(auto room : Resources::rooms)
	{
		if(!room.at("visited").get<bool>()) continue;

		//Shape of room
		auto shape = createRoomShape(room, scale, outlineThickness);

		//Bounds
		if(shape.getPosition().x < upperLeft.x) upperLeft.x = shape.getPosition().x;
		if(shape.getPosition().y < upperLeft.y) upperLeft.y = shape.getPosition().y;
		if(shape.getPosition().x + shape.getSize().x > lowerRight.x) lowerRight.x = shape.getPosition().x + shape.getSize().x;
		if(shape.getPosition().y + shape.getSize().y > lowerRight.y) lowerRight.y = shape.getPosition().y + shape.getSize().y;

		if(room.at("name").get<std::string>() == getCurrentRoom().getRoomName()) //current room
		{
			shape.setOutlineColor(sf::Color::Red);
			currentRoomShape = shape;
		}
		else roomShapes.push_back(shape);
	}

	const auto center = sf::Vector2f((upperLeft.x + lowerRight.x) * 0.5f, (upperLeft.y + lowerRight.y) * 0.5f);
	const auto size = sf::Vector2f(fabs(upperLeft.x - lowerRight.x), fabs(upperLeft.y - lowerRight.y));
	const auto background = createMiniMapBackground(size);

	drawMiniMap(background, currentRoomShape, roomShapes, center);
}

/* Sebastian Pietras */
void Game::initializePlayer(const bool def)
{
	auto& data = def ? Resources::defaultPlayerData : Resources::playerData;

	const sf::Vector2f playerPosition(data.at("positionX").get<float>(),
	                                  data.at("positionY").get<float>());
	const sf::Vector2f playerSpeed(data.at("speed").get<float>(),
	                               data.at("jumpSpeed").get<float>());
	const auto gravity = data.at("gravity").get<float>(),
	           friction = data.at("friction").get<float>(),
	           dashSpeed = data.at("dashSpeed").get<float>(),
	           mana = data.at("mana").get<float>();
	const auto roomName = data.at("startingRoom").get<std::string>();
	const auto hp = data.at("hp").get<int>(),
	           dashDamage = data.at("dashDamage").get<int>();

	player_ = Player(Resources::textures.at("player"),
	                 playerPosition,
	                 playerSpeed,
	                 gravity,
	                 friction,
	                 roomName,
	                 hp,
	                 mana,
	                 dashSpeed,
	                 dashDamage);

	Resources::getRoomJson(roomName).at("visited") = true;
}


/* Sebastian Pietras */
void Game::setKeys()
{
	for(auto& room : loadedRooms_)
	{
		for(auto& key : room.second.getKeys())
		{
			auto& doorRoom = loadedRooms_[key.getDoorRoomName()];
			for(auto& door : doorRoom.getDoors())
			{
				if(door.getId() == key.getDoorId())
				{
					key.setDoor(&door);
					break;
				}
			}
		}
	}
}

/* Sebastian Pietras, Bernard Lesiewicz */
Game::Game(const sf::VideoMode mode, const std::string& title)
	: window_(mode, title)
{
	window_.setVisible(false);
	window_.setMouseCursorVisible(false);

	try { Resources::load(); }
	catch(const std::exception& e) { throw std::runtime_error("Can't load resources.\n" + std::string(e.what())); }

	loadedRooms_ = Resources::createRooms();
	setKeys();
	try { enemies_ = Resources::createEnemies(); }
	catch(const std::exception& e) { throw std::runtime_error("Can't create enemies.\n" + std::string(e.what())); }

	try { initializePlayer(); }
	catch(const std::exception& e) { throw std::runtime_error("Can't initialize player.\n" + std::string(e.what())); }

	playerHealthText_.setFont(Resources::fonts["vcr"]);
	playerHealthText_.setFillColor(sf::Color::White);
	playerHealthText_.setOutlineColor(sf::Color::Black);
	playerHealthText_.setOutlineThickness(1.0f);
	playerHealthText_.setPosition(10.0f, 10.0f);
	playerHealthText_.setCharacterSize(20);

	manaText_.setFont(Resources::fonts["vcr"]);
	manaText_.setFillColor(sf::Color::White);
	manaText_.setOutlineColor(sf::Color::Black);
	manaText_.setOutlineThickness(1.0f);
	manaText_.setPosition(100.0f, 10.0f);
	manaText_.setCharacterSize(20);

	view_ = sf::View(player_.getCenter(), sf::Vector2f(window_.getSize()));

	scaleView();

	window_.setView(view_);
	window_.setVisible(true);
}

/* Sebastian Pietras */
bool Game::play()
{
	try
	{
		if(!handleWindowEvents()) return false; //Check what happened with window

		handleInput(); //Check pressed keys

		auto deltaTime = clock_.restart().asSeconds();
		if(deltaTime > 1.0f / 60.0f) deltaTime = 1.0f / 60.0f; //limit deltaTime, so it can't be big

		update(deltaTime); //update everything that is moving
		if(player_.getHp() <= 0) restart();

		draw(); //draw everything to the screen
		checkErrorWindows();

		return true;
	}
	catch(const std::exception& e1)
	{
		try
		{
			save();
		}
		catch(const std::exception& e2)
		{
			throw std::runtime_error("Runtime error.\n" + std::string(e1.what()) + "\nCouldn't save :(\n" + e2.what());
		}

		throw std::runtime_error("Runtime error.\n" + std::string(e1.what()) + "\nGame saved :)");
	}
}
