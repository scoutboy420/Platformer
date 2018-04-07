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
			auto push = player_.checkPush(entity);
			if(push.y > 0) player_.onGround = true; //if it pushes the player upwards, then the player is on top of something
			player_.move(push);
		}
	}
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
			break;
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

	view_.setCenter(player_.getCenter());
}

void Game::draw()
{
	window_.clear(currentRoom_.getBackground());

	const sf::IntRect viewInt = sf::IntRect(view_.getViewport());

	for(const auto& entity : currentRoom_.getEntities())
	{
		if(entity.getBody().getTextureRect().intersects(viewInt)) //draw only entities that are inside view
		{
			window_.draw(entity.getBody());
		}
	}

	window_.draw(player_.getBody());

	window_.setView(view_);

	window_.display();
}

Game::Game(sf::VideoMode mode, std::string title) : window_(mode, title)
{
	window_.setVisible(false);

	Resources::load();

	currentRoom_ = Room(Resources::getStartingRoomId());

	sf::Vector2f playerPosition(Resources::playerData_.at("positionX").get<float>(),
	                            Resources::playerData_.at("positionY").get<float>());
	sf::Vector2f playerSpeed(Resources::playerData_.at("speed").get<float>(),
	                         Resources::playerData_.at("jumpSpeed").get<float>());
	sf::Vector2f playerDrag(Resources::playerData_.at("drag").get<float>(),
	                        Resources::playerData_.at("gravity").get<float>());

	player_ = Player(Resources::textures_.at("player"), playerPosition, playerSpeed, playerDrag);

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
