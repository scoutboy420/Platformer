#include "Game.h"
#include "Utilities/Resources.h"
#include "Utilities/JSON/json.hpp"

/* Sebastian Pietras, Bernard Lesiewicz*/
void Game::checkCollisions(float deltaTime)
{
	player_.onGround = false;

	for(const auto& entity : currentRoom_.getEntities())
	{
		if(player_.collides(entity))
		{
			const auto push = player_.checkPush(entity, deltaTime);
			if(push.y > 0) player_.onGround = true; //if it pushes the player upwards, then the player is on top of something
			player_.move(push);

			printf("Position: %f,%f, Push: %f,%f\n", player_.getCenter().x, player_.getCenter().y, push.x, push.y);

			if(push.y != 0.0f) player_.stopY();
		}
	}
	for(const auto& key : currentRoom_.getKeys())
    {
        int id = key.getId();
        if(player_.collides(key) && openedDoors_[id] == false)
        {
            openedDoors_[id] = true;
            //and reload/update the room
            currentRoom_ = Room(currentRoom_.getID(), openedDoors_);
        }
    }
    for(const auto& door : currentRoom_.getDoors())
	{
		if(player_.collides(door))
		{
			const auto push = player_.checkPush(door, deltaTime);
			if(push.y > 0) player_.onGround = true; //if it pushes the player upwards, then the player is on top of something
			player_.move(push);

			printf("Position: %f,%f, Push: %f,%f (locked door)\n", player_.getCenter().x, player_.getCenter().y, push.x, push.y);

			if(push.y != 0.0f) player_.stopY();
		}
	}
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

	int roomID = 0, entranceID = 0;
	sf::Vector2f offset = { 0.0f, 0.0f };
	const std::string roomName = "room" + std::to_string(currentRoom_.getID());

	//Find which entrance this entrance leads to and player position relative to this entrance
	for(const auto& entrance : Resources::rooms_.at(roomName).at("entrances"))
	{
		if(dir == Resources::direction::LEFT)
		{
			if(player_.getCenter().y >= entrance.at("y").get<float>() &&
				player_.getCenter().y <= entrance.at("y").get<float>() + entrance.at("height").get<float>() * 50.0f)
			{
				if(entrance.at("x").get<float>() == 0.0f)
				{
					roomID = entrance.at("to").at("roomID").get<int>();
					entranceID = entrance.at("to").at("entranceID").get<int>();
					offset = sf::Vector2f(-player_.getSize().x * 0.5f + 50.0f, player_.getPosition().y - entrance.at("y").get<float>());
				}
			}
		}
		else if(dir == Resources::direction::RIGHT)
		{
			if(player_.getCenter().y >= entrance.at("y").get<float>() &&
				player_.getCenter().y <= entrance.at("y").get<float>() + entrance.at("height").get<float>() * 50.0f)
			{
				if(entrance.at("x").get<float>() + 50.0f == currentRoom_.getSize().x)
				{
					roomID = entrance.at("to").at("roomID").get<int>();
					entranceID = entrance.at("to").at("entranceID").get<int>();
					offset = sf::Vector2f(-player_.getSize().x * 0.5f, player_.getPosition().y - entrance.at("y").get<float>());
				}
			}
		}
		else if(dir == Resources::direction::UP)
		{
			if(player_.getCenter().x >= entrance.at("x").get<float>() &&
				player_.getCenter().x <= entrance.at("x").get<float>() + entrance.at("width").get<float>() * 50.0f)
			{
				if(entrance.at("y").get<float>() == 0.0f)
				{
					roomID = entrance.at("to").at("roomID").get<int>();
					entranceID = entrance.at("to").at("entranceID").get<int>();
					offset = sf::Vector2f(player_.getPosition().x - entrance.at("x").get<float>(), -player_.getSize().y * 0.5f + 50.0f);
				}
			}

		}
		else if(dir == Resources::direction::DOWN)
		{
			if(player_.getCenter().x >= entrance.at("x").get<float>() &&
				player_.getCenter().x <= entrance.at("x").get<float>() + entrance.at("width").get<float>() * 50.0f)
			{
				if(entrance.at("y").get<float>() + 50.0f == currentRoom_.getSize().y)
				{
					roomID = entrance.at("to").at("roomID").get<int>();
					entranceID = entrance.at("to").at("entranceID").get<int>();
					offset = sf::Vector2f(player_.getPosition().x - entrance.at("x").get<float>(), -player_.getSize().y * 0.5f);
				}
			}
		}
	}

	changeRoom(roomID, entranceID, offset);
}

/* Sebastian Pietras */
void Game::changeRoom(int roomID, int entranceID, sf::Vector2f offset)
{
	const std::string roomName = "room" + std::to_string(roomID);

	currentRoom_ = Room(roomID, openedDoors_);

	sf::Vector2f entrancePos = { 0.0f, 0.0f };

	for(const auto& entrances : Resources::rooms_.at(roomName).at("entrances"))
	{
		if(entrances.at("id").get<int>() == entranceID)
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
	float camX = player_.getCenter().x, camY = player_.getCenter().y;

	//Bound camera if it goes outside walls (assuming room is rectangular)
	if(camX - view_.getSize().x * 0.5f < 0.0f) camX += (view_.getSize().x * 0.5f - camX);
	if(camX + view_.getSize().x * 0.5f > currentRoom_.getSize().x) camX -= (camX + view_.getSize().x * 0.5f - currentRoom_.getSize().x);
	if(camY - view_.getSize().y * 0.5f < 0.0f) camY += (view_.getSize().y * 0.5f - camY);
	if(camY + view_.getSize().y * 0.5f > currentRoom_.getSize().y) camY -= (camY + view_.getSize().y * 0.5f - currentRoom_.getSize().y);

	view_.setCenter(camX, camY);
}

/* Sebastian Pietras */
void Game::scaleView()
{
	view_.setSize(sf::Vector2f(window_.getSize()));
	//If current view is bigger than entire room, scale it down to fit entire room (and no more)

	const float ratioX = currentRoom_.getSize().x / view_.getSize().x, ratioY = currentRoom_.getSize().y / view_.getSize().y;
	const float dominatingRatio = std::min(ratioX, ratioY);

	if(dominatingRatio < 1.0f) view_.zoom(dominatingRatio);
}

/* Sebastian Pietras */
void Game::handleInput()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		player_.run(Resources::direction::RIGHT);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player_.run(Resources::direction::LEFT);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player_.jump();
	}
}

/* Sebastian Pietras */
bool Game::handleWindowEvents()
{
	sf::Event e;

	while(window_.pollEvent(e))
	{
		switch(e.type)
		{
			case sf::Event::Closed:
			{
				//Save all data
				Resources::playerData_.at("positionX") = player_.getPosition().x;
				Resources::playerData_.at("positionY") = player_.getPosition().y;
				Resources::playerData_.at("startingRoom") = "room" + std::to_string(currentRoom_.getID());
//				Resources::save();
				window_.close();
				return false;
			}
			case sf::Event::Resized:
			{
				scaleView();
			}
		default:
			break;
		}
	}

	return true;
}

/* Sebastian Pietras */
void Game::update(float deltaTime)
{
	player_.update(deltaTime);

	checkCollisions(deltaTime);

	checkRoomChange();

	checkCamera();
}

/* Sebastian Pietras, Bernard Lesiewicz */
void Game::draw()
{
	window_.clear(sf::Color::Black);

	window_.setView(view_);

	window_.draw(currentRoom_.getBackground());

	const auto viewRect = sf::FloatRect(view_.getCenter() - sf::Vector2f(view_.getSize().x * 0.5f, view_.getSize().y * 0.5f), view_.getSize());

	for(const auto& entity : currentRoom_.getEntities())
	{
		const auto entityRect = entity.getBody().getGlobalBounds();
		if(viewRect.intersects(entityRect)) //draw only entities that are inside view
		{
			window_.draw(entity.getBody());
		}
	}

    for(const auto& door : currentRoom_.getDoors())
	{
		const auto entityRect = door.getBody().getGlobalBounds();
		if(viewRect.intersects(entityRect)) //draw only entities that are inside view
		{
			window_.draw(door.getBody());
		}
	}

	for(const auto& key : currentRoom_.getKeys())
	{
		const auto entityRect = key.getBody().getGlobalBounds();
		if(viewRect.intersects(entityRect)) //draw only entities that are inside view
		{
			window_.draw(key.getBody());
		}
	}

	window_.draw(player_.getBody());

	for(auto e : currentRoom_.getGradientEdges())
	{
		window_.draw(e.data(), 4, sf::Quads);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab))
		showMiniMap();

	window_.display();
}

/* Sebastian Pietras */
void Game::showMiniMap()
{
	std::vector<sf::RectangleShape> roomShapes;
	sf::RectangleShape currentRoomShape;
	sf::Vector2f upperLeft = sf::Vector2f(0.0f, 0.0f), lowerRight = sf::Vector2f(0.0f, 0.0f);

	const float outlineThickness = 2.0f;
	const float scale = std::min(float(window_.getSize().x), float(window_.getSize().y)) / 50.0f;

	for(auto it = Resources::rooms_.begin(); it != Resources::rooms_.end(); ++it)
	{
		if(!it.value().at("visited").get<bool>()) continue;

		//Shape of room
		sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(it.value().at("width").get<float>() * scale - outlineThickness, it.value().at("height").get<float>() * scale - outlineThickness));
		shape.setPosition(it.value().at("globalX").get<float>() / 50.0f * scale, it.value().at("globalY").get<float>() / 50.0f * scale);

		//Bounds
		if(shape.getPosition().x < upperLeft.x) upperLeft.x = shape.getPosition().x;
		if(shape.getPosition().y < upperLeft.y) upperLeft.y = shape.getPosition().y;
		if(shape.getPosition().x + shape.getSize().x > lowerRight.x) lowerRight.x = shape.getPosition().x + shape.getSize().x;
		if(shape.getPosition().y + shape.getSize().y > lowerRight.y) lowerRight.y = shape.getPosition().y + shape.getSize().y;

		const int r = it.value().at("colorR").get<int>();
		const int g = it.value().at("colorG").get<int>();
		const int b = it.value().at("colorB").get<int>();

		shape.setFillColor(sf::Color(r, g, b));

		shape.setOutlineColor(sf::Color::Blue);
		shape.setOutlineThickness(outlineThickness);

		if(it.key() == "room" + std::to_string(currentRoom_.getID())) //current room
		{
			shape.setOutlineColor(sf::Color::Red);
			currentRoomShape = shape;
		}
		else roomShapes.push_back(shape);
	}

	const sf::Vector2f center = sf::Vector2f((upperLeft.x + lowerRight.x)*0.5f, (upperLeft.y + lowerRight.y)*0.5f);
	const sf::Vector2f size = sf::Vector2f(fabs(upperLeft.x - lowerRight.x), fabs(upperLeft.y - lowerRight.y));
	//Background
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(size.x * 1.25f, size.y * 1.25f));
	background.setPosition(sf::Vector2f(window_.getSize().x * 0.5f, window_.getSize().y * 0.5f) - sf::Vector2f(background.getSize().x * 0.5f, background.getSize().y * 0.5f));
	background.setFillColor(sf::Color::Black);
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(outlineThickness);

	//Draw minimap independently of current view
	window_.setView(sf::View(sf::Vector2f(window_.getSize().x * 0.5f, window_.getSize().y * 0.5f), sf::Vector2f(window_.getSize())));

	window_.draw(background);

	for(auto shape : roomShapes)
	{
		//Transform from local to global position
		shape.setPosition(sf::Vector2f(window_.getSize().x * 0.5f, window_.getSize().y * 0.5f) - center + shape.getPosition());
		window_.draw(shape);
	}

	currentRoomShape.setPosition(sf::Vector2f(window_.getSize().x * 0.5f, window_.getSize().y * 0.5f) - center + currentRoomShape.getPosition());
	window_.draw(currentRoomShape);
}

/* Sebastian Pietras, Bernard Lesiewicz */
Game::Game(sf::VideoMode mode, std::string title) : window_(mode, title)
{
	window_.setVisible(false);

	Resources::load();

    int n = Resources::highestDoorId();     //all doors are closed at the beginning
	for(int i=0; i<=n; i++)
    {
        openedDoors_.push_back(false);
    }

	currentRoom_ = Room(Resources::getRoomId(Resources::playerData_.at("startingRoom").get<std::string>()), openedDoors_);

	const sf::Vector2f playerPosition(Resources::playerData_.at("positionX").get<float>(),
	                                  Resources::playerData_.at("positionY").get<float>());
	const sf::Vector2f playerSpeed(Resources::playerData_.at("speed").get<float>(),
	                               Resources::playerData_.at("jumpSpeed").get<float>());
	const auto gravity = Resources::playerData_.at("gravity").get<float>();
	const auto friction = Resources::playerData_.at("friction").get<float>();

	player_ = Player(Resources::textures_.at("player"), playerPosition, playerSpeed, gravity, friction);

	checkCollisions(0.0f);      //not sure how big deltaTime should be

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

	float deltaTime = clock_.restart().asSeconds();
	if(deltaTime > 1.0f / 60.0f) deltaTime = 1.0f / 60.0f; //limit deltaTime, so it can't be big

	update(deltaTime); //update everything that is moving
	draw(); //draw everything to the screen

	return true;
}
