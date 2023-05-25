#include "Level.h"

Player::Player()
{
	texture.loadFromFile("./player.png");
	
	sprite.setTexture(texture);
	sprite.setColor(sf::Color::Green);
	sprite.setPosition(sf::Vector2f(20.f, FLOOR-60));
	sprite.setScale(sf::Vector2f(0.6f, 0.6f));
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}


Block::Block()
{
	rectangle.setSize(sf::Vector2f(60, 60));
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(5);
	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setPosition(10, FLOOR - rectangle.getSize().y
		- rectangle.getOutlineThickness());

}

Block::~Block()
{

}
Spike::Spike()
{}

Spike::Spike(int _x, int _y ,sf::Color color)
{
	x = _x;
	y = _y;
	triangle = sf::VertexArray(sf::Triangles, 3);

	triangle[0].position = sf::Vector2f(x+GRID_WIDTH/2, y);
	triangle[1].position = sf::Vector2f(x-GRID_WIDTH/2, y);
	triangle[2].position = sf::Vector2f(x, y-GRID_HIGHT);

	triangle[0].color = color;
	triangle[1].color = color;
	triangle[2].color = sf::Color::Black;

}

void Spike::draw(sf::RenderWindow& window)
{
	window.draw(triangle);
	//window.draw(tri);
}

void Block::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
}

Level::Level()
{

	floor.setSize(sf::Vector2f(1280, 3));
	floor.setFillColor(sf::Color::White);
	floor.setOutlineThickness(0);
	floor.setPosition(0, FLOOR);

	spike = Spike(100, FLOOR, sf::Color::Red);
}

Level::~Level()
{

}

void Level::draw(sf::RenderWindow& window)
{
	sf::View view(sf::FloatRect(0, 0, 1280, 720));
	window.setView(view);
	window.clear();
	block.draw(window);
	spike.draw(window);
	player.draw(window);
	window.draw(floor);
}