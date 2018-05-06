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
	if(player_.getCenter().x <= 0.0f) dir = Resources::direction::LEFT;
	else if(player_.getCenter().x >= currentRoom_.getSize().x) dir = Resources::direction::RIGHT;
	else if(player_.getCenter().y <= 0.0f) dir = Resources::direction::UP;
	else if(player_.getCenter().y >= currentRoom_.getSize().y) dir = Resources::direction::DOWN;
	else return;

	changeRoom(dir);
}

void Game::changeRoom(Resources::direction dir)
{
	const std::string dirName = Resources::directionToString(dir);
	const std::string oldRoomName = "room" + std::to_string(currentRoom_.getID());
	const std::string currentRoomName = Resources::map_.at(oldRoomName).at(dirName).get<std::string>();

	currentRoom_ = Room(Resources::getRoomId(currentRoomName));
	auto oldEntrances = Resources::rooms_.at(oldRoomName).at("entrances");
	auto currentEntrances = Resources::rooms_.at(currentRoomName).at("entrances");

	//Change player's position to equivalent entrance at new room

	if(dir == Resources::direction::LEFT)
		player_.setPosition(
			{
				currentEntrances.at("right").at("x").get<float>(),
				currentEntrances.at("right").at("y").get<float>() + (player_.getPosition().y - oldEntrances.at("left").at("y").get<float>())
			});
	else if(dir == Resources::direction::RIGHT)
		player_.setPosition(
			{
				currentEntrances.at("left").at("x").get<float>(),
				currentEntrances.at("left").at("y").get<float>() + (player_.getPosition().y - oldEntrances.at("right").at("y").get<float>())
			});
	else if(dir == Resources::direction::UP)
		player_.setPosition(
			{
				currentEntrances.at("down").at("x").get<float>() + (player_.getPosition().x - oldEntrances.at("down").at("x").get<float>()),
				currentEntrances.at("down").at("y").get<float>()
			});
	else if(dir == Resources::direction::DOWN)
		player_.setPosition(
			{
				currentEntrances.at("up").at("x").get<float>() + (player_.getPosition().x - oldEntrances.at("up").at("x").get<float>()),
				currentEntrances.at("up").at("y").get<float>()
			});

	scaleView(); //Scale view if new room is smaller than old room
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
			window_.close();
			return false;
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

	currentRoom_ = Room(Resources::getRoomId(Resources::map_.at("startingRoom").get<std::string>()));

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
