#include "Level.h"

Player::Player()
{
	texture.loadFromFile("res/player.png");
	
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(20.f, FLOOR-60));
}

void Player::draw(sf::RenderWindow& window)
{
	sprite.move(sf::Vector2f(1.f, 0.f));
	window.draw(sprite);
}


Block::Block(int _x, int _y, const sf::Color& color)
{
	x = _x * GRID_WIDTH;
	y = _y * GRID_HIGHT;


	block = sf::VertexArray(sf::Quads, 4);

	block[0].position = sf::Vector2f(x, FLOOR - y);
	block[1].position = sf::Vector2f(x, FLOOR - y - GRID_HIGHT);
	block[2].position = sf::Vector2f(x+GRID_WIDTH, FLOOR - y - GRID_HIGHT);
	block[3].position = sf::Vector2f(x+GRID_WIDTH, FLOOR - y);

	block[0].color = color;
	block[1].color = sf::Color::Black;
	block[2].color = sf::Color::Black;
	block[3].color = color;

	t.loadFromFile("res/glow.png");
	s.setTexture(t);
	s.setPosition(x-3, FLOOR - y - GRID_HIGHT-3);

}

void Block::draw(sf::RenderWindow& window)
{
	window.draw(block);
	window.draw(s);
	//window.draw(rectangle);
}

Block::~Block()
{

}
Spike::Spike()
{
}

Spike::Spike(int _x, int _y ,sf::Color color)
{
	x = _x * GRID_WIDTH;
	y = _y * GRID_HIGHT;
	triangle = sf::VertexArray(sf::Triangles, 3);

	triangle[0].position = sf::Vector2f(x, FLOOR - y);
	triangle[1].position = sf::Vector2f(x+GRID_WIDTH/2, FLOOR - y - GRID_HIGHT);
	triangle[2].position = sf::Vector2f(x + GRID_WIDTH, FLOOR - y);

	triangle[0].color = color;
	triangle[1].color = sf::Color::Black;
	triangle[2].color = color;

	tx.loadFromFile("res/triangle_glow.png");

	sp.setTexture(tx);
	sp.setPosition(x - 3, FLOOR - y - GRID_HIGHT-2);
	
}

void Spike::draw(sf::RenderWindow& window)
{
	window.draw(triangle);
	window.draw(sp);
	//window.draw(tri);
}


Level::Level()
{

	floor.setSize(sf::Vector2f(1280, 3));
	floor.setFillColor(sf::Color::White);
	floor.setOutlineThickness(0);
	floor.setPosition(0, FLOOR);

}

Level::~Level()
{

}

void Level::draw(sf::RenderWindow& window)
{
	sf::View view(sf::FloatRect(0, 0, 1280, 720));
	
	window.setView(view);
	
	window.clear(sf::Color::Black);
	block.draw(window);
	block2.draw(window);
	spike.draw(window);
	player.draw(window);
	window.draw(floor);
}