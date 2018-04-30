#include "Game.h"
#include "Utilities/Resources.h"
#include "Utilities/JSON/json.hpp"

void Game::checkCollisions()
{
	player_.onGround = false;

	for(const auto& entity : currentRoom_.getEntities())
	{
		if(player_.collides(entity))
		{
			const auto push = player_.checkPush(entity);
			if(push.y > 0) player_.onGround = true; //if it pushes the player upwards, then the player is on top of something
			player_.move(push);

			printf("Position: %f,%f, Push: %f,%f\n", player_.getCenter().x, player_.getCenter().y, push.x, push.y);

			if(push.y != 0.0f) player_.stopY();
		}
	}
}

void Game::checkRoomChange()
{
	const std::string currentRoomName = "room" + std::to_string(currentRoom_.getID());
	Resources::direction dir;
	if(player_.getCenter().x <= 0.0f) dir = Resources::direction::LEFT;
	else if(player_.getCenter().x >= currentRoom_.getSize().x) dir = Resources::direction::RIGHT;
	else if(player_.getCenter().y <= 0.0f) dir = Resources::direction::UP;
	else if(player_.getCenter().y >= currentRoom_.getSize().y) dir = Resources::direction::DOWN;
	else return;

	const std::string roomName = Resources::map_.at(currentRoomName).at(Resources::directionToString(dir)).get<std::string>();

	currentRoom_ = Room(Resources::getRoomId(roomName));

	if(dir == Resources::direction::LEFT) player_.move({ currentRoom_.getSize().x - 1.0f, 0.0f });
	else if(dir == Resources::direction::RIGHT) player_.move({ -currentRoom_.getSize().x + 1.0f, 0.0f });
	else if(dir == Resources::direction::UP) player_.move({ 0.0f, currentRoom_.getSize().y - 1.0f });
	else if(dir == Resources::direction::DOWN) player_.move({ 0.0f, -currentRoom_.getSize().y + 1.0f });
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

	checkCollisions();

	checkRoomChange();

	view_.setCenter(player_.getCenter());
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

	checkCollisions();

	view_ = sf::View(player_.getCenter(), sf::Vector2f(mode.width, mode.height));

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
