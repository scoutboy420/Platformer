#include "Game.h"
#include "Utilities/Resources.h"
#include "Utilities/JSON/json.hpp"

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
}

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

void Game::changeRoom(int roomID, int entranceID, sf::Vector2f offset)
{
	const std::string roomName = "room" + std::to_string(roomID);

	currentRoom_ = Room(roomID);

	sf::Vector2f entrancePos = { 0.0f, 0.0f };

	for(const auto& entrances : Resources::rooms_.at(roomName).at("entrances"))
	{
		if(entrances.at("id").get<int>() == entranceID)
			entrancePos = sf::Vector2f(entrances.at("x").get<float>(), entrances.at("y").get<float>());
	}

	player_.setPosition(entrancePos + offset);

	scaleView();
}

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

void Game::scaleView()
{
	view_.setSize(defaultViewSize_);
	//If current view is bigger than entire room, scale it down to fit entire room (and no more)

	const float ratioX = currentRoom_.getSize().x / view_.getSize().x, ratioY = currentRoom_.getSize().y / view_.getSize().y;
	const float dominatingRatio = std::min(ratioX, ratioY);

	if(dominatingRatio < 1.0f) view_.zoom(dominatingRatio);
}

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

bool Game::handleWindowEvents()
{
	sf::Event e;

	while(window_.pollEvent(e))
	{
		switch(e.type)
		{
			case sf::Event::Closed:
			{
				Resources::playerData_["positionX"] = player_.getPosition().x;
				Resources::playerData_["positionY"] = player_.getPosition().y;
				Resources::playerData_["startingRoom"] = "room" + std::to_string(currentRoom_.getID());
				Resources::save();
				window_.close();
				return false;
			}
		default:
			break;
		}
	}

	return true;
}

void Game::update(float deltaTime)
{
	player_.update(deltaTime);

	checkCollisions(deltaTime);

	checkRoomChange();

	checkCamera();
}

void Game::draw()
{
	window_.clear(sf::Color::Black);

	window_.setView(view_);

	window_.draw(currentRoom_.getBackground());

	const sf::IntRect viewInt = sf::IntRect(view_.getViewport());

	for(const auto& entity : currentRoom_.getEntities())
	{
		if(entity.getBody().getTextureRect().intersects(viewInt)) //draw only entities that are inside view
		{
			window_.draw(entity.getBody());
		}
	}

	window_.draw(player_.getBody());

	for(auto e : currentRoom_.getGradientEdges())
	{
		window_.draw(e.data(), 4, sf::Quads);
	}

	window_.display();
}

Game::Game(sf::VideoMode mode, std::string title) : window_(mode, title)
{
	window_.setVisible(false);

	Resources::load();

	currentRoom_ = Room(Resources::getRoomId(Resources::playerData_.at("startingRoom").get<std::string>()));

	const sf::Vector2f playerPosition(Resources::playerData_.at("positionX").get<float>(),
	                                  Resources::playerData_.at("positionY").get<float>());
	const sf::Vector2f playerSpeed(Resources::playerData_.at("speed").get<float>(),
	                               Resources::playerData_.at("jumpSpeed").get<float>());
	const auto gravity = Resources::playerData_.at("gravity").get<float>();
	const auto friction = Resources::playerData_.at("friction").get<float>();

	player_ = Player(Resources::textures_.at("player"), playerPosition, playerSpeed, gravity, friction);

	checkCollisions(0.0f);      //not sure how big deltaTime should be

	defaultViewSize_ = sf::Vector2f(float(mode.width), float(mode.height));
	view_ = sf::View(player_.getCenter(), defaultViewSize_);

	scaleView();

	window_.setView(view_);

	window_.setVisible(true);
}

bool Game::play()
{
	if(!handleWindowEvents()) return false; //Check what happened with window

	handleInput(); //Check pressed keys

	float deltaTime = clock_.restart().asSeconds();
	if(deltaTime > 1.0f / 60.0f) deltaTime = 1.0f / 60.0f; //limit framerate to 60 fps

	update(deltaTime); //update everything that is moving
	draw(); //draw everything to the screen

	return true;
}
