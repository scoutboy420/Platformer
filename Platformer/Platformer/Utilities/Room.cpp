#include "Room.h"

/* Sebastian Pietras */
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

/* Sebastian Pietras, Bernard Lesiewicz */
Room::Room(const std::string& roomName)
{
	roomName_ = roomName;

	blocks_ = Resources::createBlocks(roomName);
	doors_ = Resources::createDoors(roomName);
	keys_ = Resources::createKeys(roomName);

	size_ = sf::Vector2f(Resources::getRoomJson(roomName).at("width").get<float>() * 50.0f,
	                     Resources::getRoomJson(roomName).at("height").get<float>() * 50.0f);
	addGradient();

	const auto r = Resources::getRoomJson(roomName).at("colorR").get<int>();
	const auto g = Resources::getRoomJson(roomName).at("colorG").get<int>();
	const auto b = Resources::getRoomJson(roomName).at("colorB").get<int>();

	backgroundColor_ = sf::Color(r, g, b);

	background_ = sf::RectangleShape(size_);
	background_.setFillColor(backgroundColor_);
}
