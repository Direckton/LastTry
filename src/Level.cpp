#include "Level.h"

Level::Level()
{
	rectangle.setSize(sf::Vector2f(60, 60));
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(5);
	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setPosition(10, 20);
}

Level::~Level()
{

}

void Level::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
}