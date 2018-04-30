#include "Room.h"
#include "Resources.h"

void Room::calculateSize()
{
	if(blocks_.empty())
	{
		size_ = { 0.0f, 0.0f };
		return;
	}
	
	sf::Vector2f lowerRight = blocks_[0].getPosition();

	for(const auto& b : blocks_)
	{
		const sf::Vector2f pos = b.getPosition();

		if(pos.x > lowerRight.x) lowerRight = pos;
		else if(pos.y > lowerRight.y) lowerRight = pos;
	}

	size_ = { lowerRight.x + 50.0f, lowerRight.y + 50.0f };
}

void Room::addGradient()
{

	gradientEdges_.push_back({
		sf::Vertex({ 0.0f, 0.0f }, sf::Color::Black),
		sf::Vertex({ 0.0f, size_.y }, sf::Color::Black),
		sf::Vertex({ 50.0f, size_.y }, sf::Color::Transparent),
		sf::Vertex({ 50.0f, 0.0f }, sf::Color::Transparent)
	});

	gradientEdges_.push_back({
		sf::Vertex({ 0.0f, 0.0f }, sf::Color::Black),
		sf::Vertex({ size_.x, 0.0f }, sf::Color::Black),
		sf::Vertex({ size_.x, 50.0f }, sf::Color::Transparent),
		sf::Vertex({ 0.0f, 50.0f }, sf::Color::Transparent)
		});

	gradientEdges_.push_back({
		sf::Vertex({ size_.x, 0.0f }, sf::Color::Black),
		sf::Vertex({ size_.x, size_.y }, sf::Color::Black),
		sf::Vertex({ size_.x - 50.0f, size_.y }, sf::Color::Transparent),
		sf::Vertex({ size_.x - 50.0f, 0.0f }, sf::Color::Transparent)
		});

	gradientEdges_.push_back({
		sf::Vertex({ 0.0f, size_.y }, sf::Color::Black),
		sf::Vertex({ size_.x, size_.y }, sf::Color::Black),
		sf::Vertex({ size_.x, size_.y - 50.0f }, sf::Color::Transparent),
		sf::Vertex({ 0.0f, size_.y - 50.0f }, sf::Color::Transparent)
		});
}

Room::Room(int roomId)
{
	blocks_ = Resources::createEntities(roomId);

	calculateSize();
	addGradient();

	const std::string roomName = "room" + std::to_string(roomId);

	const int r = Resources::rooms_.at(roomName).at("colorR").get<int>();
	const int g = Resources::rooms_.at(roomName).at("colorG").get<int>();
	const int b = Resources::rooms_.at(roomName).at("colorB").get<int>();

	backgroundColor_ = sf::Color(r, g, b);

	background_ = sf::RectangleShape(size_);
	background_.setFillColor(backgroundColor_);
}
