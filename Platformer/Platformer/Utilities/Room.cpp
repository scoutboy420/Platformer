#include "Room.h"
#include "Resources.h"

void Room::addGradient()
{
	//Assumes that wall blocks are 50x50

	//left
	gradientEdges_.push_back({
		sf::Vertex({0.0f, 0.0f}, sf::Color::Black),
		sf::Vertex({0.0f, size_.y}, sf::Color::Black),
		sf::Vertex({50.0f, size_.y}, sf::Color::Transparent),
		sf::Vertex({50.0f, 0.0f}, sf::Color::Transparent)
	});

	//up
	gradientEdges_.push_back({
		sf::Vertex({0.0f, 0.0f}, sf::Color::Black),
		sf::Vertex({size_.x, 0.0f}, sf::Color::Black),
		sf::Vertex({size_.x, 50.0f}, sf::Color::Transparent),
		sf::Vertex({0.0f, 50.0f}, sf::Color::Transparent)
	});

	//right
	gradientEdges_.push_back({
		sf::Vertex({size_.x, 0.0f}, sf::Color::Black),
		sf::Vertex({size_.x, size_.y}, sf::Color::Black),
		sf::Vertex({size_.x - 50.0f, size_.y}, sf::Color::Transparent),
		sf::Vertex({size_.x - 50.0f, 0.0f}, sf::Color::Transparent)
	});

	//down
	gradientEdges_.push_back({
		sf::Vertex({0.0f, size_.y}, sf::Color::Black),
		sf::Vertex({size_.x, size_.y}, sf::Color::Black),
		sf::Vertex({size_.x, size_.y - 50.0f}, sf::Color::Transparent),
		sf::Vertex({0.0f, size_.y - 50.0f}, sf::Color::Transparent)
	});
}

Room::Room(int roomId)
{
	id_ = roomId;
	const std::string roomName = "room" + std::to_string(roomId);

	blocks_ = Resources::createEntities(roomId);

	size_ = sf::Vector2f(Resources::rooms_.at(roomName).at("width").get<float>() * 50.0f, Resources::rooms_.at(roomName).at("height").get<float>() * 50.0f);
	addGradient();

	const int r = Resources::rooms_.at(roomName).at("colorR").get<int>();
	const int g = Resources::rooms_.at(roomName).at("colorG").get<int>();
	const int b = Resources::rooms_.at(roomName).at("colorB").get<int>();

	backgroundColor_ = sf::Color(r, g, b);

	background_ = sf::RectangleShape(size_);
	background_.setFillColor(backgroundColor_);
}
