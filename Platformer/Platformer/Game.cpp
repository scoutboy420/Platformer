#include "Game.h"
#include "Utilities/Resources.h"
#include "Utilities/JSON/json.hpp"

/* Sebastian Pietras */
void Game::checkBlockCollision(const float deltaTime, const Entity& entity)
{
	if(player_.collides(entity))
	{
		const auto push = player_.checkPush(entity, deltaTime);
		if(push.y > 0) //if it pushes the player upwards, then the player is on top of something
		{
			player_.onGround = true;
			if(-player_.getVelocity().y >= 2000.0f) //fall damage
				player_.hurt(int((-player_.getVelocity().y - 2000.0f) * 0.02f));
		}
		player_.move(push);

		if(push.y != 0.0f) player_.stopY();
	}
}

/* Sebastian Pietras, Bernard Lesiewicz*/
void Game::checkCollisions(const float deltaTime)
{
	player_.onGround = false;

	for(const auto& entity : currentRoom_.getEntities()) checkBlockCollision(deltaTime, entity);
	for(const auto& key : currentRoom_.getKeys())
	{
		const auto id = key.getId();
		if(player_.collides(key) && !openedDoors_[id])
		{
			openedDoors_[id] = true;
			//and reload/update the room
			currentRoom_ = Room(currentRoom_.getId(), openedDoors_);
		}
	}
	for(const auto& door : currentRoom_.getDoors()) checkBlockCollision(deltaTime, door);
}

/* Sebastian Pietras */
bool Game::findTransportLocation(const Resources::direction dir,
                                 const nlohmann::json& entrance,
                                 int& roomId,
                                 int& entranceId,
                                 sf::Vector2f& offset) const
{
	switch(dir)
	{
	case Resources::direction::LEFT: if(player_.getCenter().y >= entrance.at("y").get<float>() &&
			player_.getCenter().y <= entrance.at("y").get<float>() + entrance.at("height").get<float>() * 50.0f)
		{
			if(entrance.at("x").get<float>() == 0.0f)
			{
				roomId = entrance.at("to").at("roomID").get<int>();
				entranceId = entrance.at("to").at("entranceID").get<int>();
				offset = sf::Vector2f(-player_.getSize().x * 0.5f + 50.0f, player_.getPosition().y - entrance.at("y").get<float>());
				return true;
			}
		}
		break;
	case Resources::direction::RIGHT: if(player_.getCenter().y >= entrance.at("y").get<float>() &&
			player_.getCenter().y <= entrance.at("y").get<float>() + entrance.at("height").get<float>() * 50.0f)
		{
			if(entrance.at("x").get<float>() + 50.0f == currentRoom_.getSize().x)
			{
				roomId = entrance.at("to").at("roomID").get<int>();
				entranceId = entrance.at("to").at("entranceID").get<int>();
				offset = sf::Vector2f(-player_.getSize().x * 0.5f, player_.getPosition().y - entrance.at("y").get<float>());
				return true;
			}
		}
		break;
	case Resources::direction::UP: if(player_.getCenter().x >= entrance.at("x").get<float>() &&
			player_.getCenter().x <= entrance.at("x").get<float>() + entrance.at("width").get<float>() * 50.0f)
		{
			if(entrance.at("y").get<float>() == 0.0f)
			{
				roomId = entrance.at("to").at("roomID").get<int>();
				entranceId = entrance.at("to").at("entranceID").get<int>();
				offset = sf::Vector2f(player_.getPosition().x - entrance.at("x").get<float>(), -player_.getSize().y * 0.5f + 50.0f);
				return true;
			}
		}
		break;
	case Resources::direction::DOWN: if(player_.getCenter().x >= entrance.at("x").get<float>() &&
			player_.getCenter().x <= entrance.at("x").get<float>() + entrance.at("width").get<float>() * 50.0f)
		{
			if(entrance.at("y").get<float>() + 50.0f == currentRoom_.getSize().y)
			{
				roomId = entrance.at("to").at("roomID").get<int>();
				entranceId = entrance.at("to").at("entranceID").get<int>();
				offset = sf::Vector2f(player_.getPosition().x - entrance.at("x").get<float>(), -player_.getSize().y * 0.5f);
				return true;
			}
		}
		break;
	}

	return false;
}

/* Sebastian Pietras */
void Game::checkRoomChange()
{
	Resources::direction dir;
	if(player_.getCenter().x < 0.0f) dir = Resources::direction::LEFT;
	else if(player_.getCenter().x > currentRoom_.getSize().x) dir = Resources::direction::RIGHT;
	else if(player_.getCenter().y < 0.0f) dir = Resources::direction::UP;
	else if(player_.getCenter().y > currentRoom_.getSize().y) dir = Resources::direction::DOWN;
	else return;

	//Messy and assumes blocks are 50x50 but works

	auto roomId = 0, entranceId = 0;
	sf::Vector2f offset = {0.0f, 0.0f};
	const auto roomName = "room" + std::to_string(currentRoom_.getId());

	//Find which entrance this entrance leads to and player position relative to this entrance
	for(const auto& entrance : Resources::rooms.at(roomName).at("entrances"))
	{
		if(findTransportLocation(dir, entrance, roomId, entranceId, offset)) break;
	}

	changeRoom(roomId, entranceId, offset);
}

/* Sebastian Pietras */
void Game::changeRoom(const int roomId, const int entranceId, const sf::Vector2f offset)
{
	const auto roomName = "room" + std::to_string(roomId);

	currentRoom_ = Room(roomId, openedDoors_);

	sf::Vector2f entrancePos = {0.0f, 0.0f};

	for(const auto& entrances : Resources::rooms.at(roomName).at("entrances"))
	{
		if(entrances.at("id").get<int>() == entranceId)
		{
			entrancePos = sf::Vector2f(entrances.at("x").get<float>(), entrances.at("y").get<float>());
			break;
		}
	}

	player_.setPosition(entrancePos + offset); //Apply offset so movement can be smooth

	scaleView();
}

/* Sebastian Pietras */
void Game::checkCamera()
{
	auto camX = player_.getCenter().x, camY = player_.getCenter().y;

	//Bound camera if it goes outside walls (assuming room is rectangular)
	if(camX - view_.getSize().x * 0.5f < 0.0f)
		camX += view_.getSize().x * 0.5f - camX;

	if(camX + view_.getSize().x * 0.5f > currentRoom_.getSize().x)
		camX -= camX + view_.getSize().x * 0.5f - currentRoom_.getSize().x;

	if(camY - view_.getSize().y * 0.5f < 0.0f)
		camY += view_.getSize().y * 0.5f - camY;

	if(camY + view_.getSize().y * 0.5f > currentRoom_.getSize().y)
		camY -= camY + view_.getSize().y * 0.5f - currentRoom_.getSize().y;

	view_.setCenter(camX, camY);
}

/* Sebastian Pietras */
void Game::scaleView()
{
	view_.setSize(sf::Vector2f(window_.getSize()));
	//If current view is bigger than entire room, scale it down to fit entire room (and no more)

	const auto ratioX = currentRoom_.getSize().x / view_.getSize().x,
	           ratioY = currentRoom_.getSize().y / view_.getSize().y;
	const auto dominatingRatio = std::min(ratioX, ratioY);

	if(dominatingRatio < 1.0f) view_.zoom(dominatingRatio);
}

/* Sebastian Pietras */
void Game::handleInput()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) player_.run(Resources::direction::RIGHT);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player_.run(Resources::direction::LEFT);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) player_.jump();
}

/* Sebastian Pietras */
void Game::save() const
{
	Resources::playerData.at("positionX") = player_.getPosition().x;
	Resources::playerData.at("positionY") = player_.getPosition().y;
	Resources::playerData.at("startingRoom") = "room" + std::to_string(currentRoom_.getId());
	//Resources::save();
}

/* Sebastian Pietras */
bool Game::handleWindowEvents()
{
	sf::Event e{};

	while(window_.pollEvent(e))
	{
		switch(e.type)
		{
		case sf::Event::Closed: save();
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
	player_.update(deltaTime);

	checkCollisions(deltaTime);

	checkRoomChange();

	checkCamera();
}

/* Sebastian Pietras */
bool Game::isInsideView(const sf::FloatRect& viewRect, const Entity& entity)
{
	const auto entityRect = entity.getBody().getGlobalBounds();
	return viewRect.intersects(entityRect);
}

/* Sebastian Pietras */
void Game::drawEntities()
{
	const auto viewRect = sf::FloatRect(view_.getCenter() - sf::Vector2f(view_.getSize().x * 0.5f,
	                                                                     view_.getSize().y * 0.5f),
	                                    view_.getSize());

	for(const auto& entity : currentRoom_.getEntities()) if(isInsideView(viewRect, entity)) window_.draw(entity.getBody());

	for(const auto& door : currentRoom_.getDoors()) if(isInsideView(viewRect, door)) window_.draw(door.getBody());

	for(const auto& key : currentRoom_.getKeys()) if(isInsideView(viewRect, key)) window_.draw(key.getBody());

	window_.draw(player_.getBody());
}

/* Sebastian Pietras */
void Game::drawOverlay()
{
	for(auto e : currentRoom_.getGradientEdges()) window_.draw(e.data(), 4, sf::Quads);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)) showMiniMap();

	window_.setView(sf::View(sf::Vector2f(window_.getSize().x * 0.5f, window_.getSize().y * 0.5f),
	                         sf::Vector2f(window_.getSize())));
	playerHealthText_.setString(std::to_string(player_.getHp()));
	window_.draw(playerHealthText_);
}

/* Sebastian Pietras, Bernard Lesiewicz */
void Game::draw()
{
	window_.clear(sf::Color::Black);
	window_.setView(view_);
	window_.draw(currentRoom_.getBackground());

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
void Game::showMiniMap()
{
	std::vector<sf::RectangleShape> roomShapes;
	sf::RectangleShape currentRoomShape;
	auto upperLeft = sf::Vector2f(0.0f, 0.0f), lowerRight = sf::Vector2f(0.0f, 0.0f);

	const auto outlineThickness = 2.0f;
	const auto scale = std::min(float(window_.getSize().x), float(window_.getSize().y)) / 50.0f;

	for(auto it = Resources::rooms.begin(); it != Resources::rooms.end(); ++it)
	{
		if(!it.value().at("visited").get<bool>()) continue;

		//Shape of room
		auto shape = createRoomShape(it.value(), scale, outlineThickness);

		//Bounds
		if(shape.getPosition().x < upperLeft.x) upperLeft.x = shape.getPosition().x;
		if(shape.getPosition().y < upperLeft.y) upperLeft.y = shape.getPosition().y;
		if(shape.getPosition().x + shape.getSize().x > lowerRight.x) lowerRight.x = shape.getPosition().x + shape.getSize().x;
		if(shape.getPosition().y + shape.getSize().y > lowerRight.y) lowerRight.y = shape.getPosition().y + shape.getSize().y;

		if(it.key() == "room" + std::to_string(currentRoom_.getId())) //current room
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
void Game::initializePlayer()
{
	const sf::Vector2f playerPosition(Resources::playerData.at("positionX").get<float>(),
	                                  Resources::playerData.at("positionY").get<float>());
	const sf::Vector2f playerSpeed(Resources::playerData.at("speed").get<float>(),
	                               Resources::playerData.at("jumpSpeed").get<float>());
	const auto gravity = Resources::playerData.at("gravity").get<float>();
	const auto friction = Resources::playerData.at("friction").get<float>();

	player_ = Player(Resources::textures.at("player"), playerPosition, playerSpeed, gravity, friction);
}


/* Sebastian Pietras, Bernard Lesiewicz */
Game::Game(const sf::VideoMode mode, const std::string& title)
	: window_(mode, title)
{
	window_.setVisible(false);

	Resources::load();

	const auto n = Resources::highestDoorId(); //all doors are closed at the beginning

	for(auto i = 0; i <= n; i++) openedDoors_.push_back(false);

	currentRoom_ = Room(Resources::getRoomId(Resources::playerData.at("startingRoom").get<std::string>()), openedDoors_);

	initializePlayer();

	playerHealthText_.setFont(Resources::fonts["vcr"]);
	playerHealthText_.setFillColor(sf::Color::White);
	playerHealthText_.setOutlineColor(sf::Color::Black);
	playerHealthText_.setOutlineThickness(1.0f);
	playerHealthText_.setPosition(10.0f, 10.0f);
	playerHealthText_.setCharacterSize(20);

	view_ = sf::View(player_.getCenter(), sf::Vector2f(window_.getSize()));

	scaleView();

	window_.setView(view_);
	window_.setVisible(true);
}

/* Sebastian Pietras */
bool Game::play()
{
	if(!handleWindowEvents()) return false; //Check what happened with window

	handleInput(); //Check pressed keys

	auto deltaTime = clock_.restart().asSeconds();
	if(deltaTime > 1.0f / 60.0f) deltaTime = 1.0f / 60.0f; //limit deltaTime, so it can't be big

	update(deltaTime); //update everything that is moving
	draw();            //draw everything to the screen

	return true;
}
