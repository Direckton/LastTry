#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"

#define GRID_WIDTH 60
#define GRID_HIGHT 60
#define FLOOR 600

class Player
{
	sf::Sprite sprite;
	sf::Texture texture;
	int x, y;
public:
	Player();

	void draw(sf::RenderWindow& window);
};

class Block
{
	sf::RectangleShape rectangle;
	sf::VertexArray block;
	//60x60px
	int x, y;

public:
	Block(int x, int y, const sf::Color& color);
	~Block();
	void draw(sf::RenderWindow& window);
};

class Spike
{
	int x, y;
	sf::Texture tx;
	sf::Sprite sp;

	sf::VertexArray triangle;
	sf::CircleShape tri;


public:
	Spike();
	Spike(int _x, int _y, sf::Color color);

	void draw(sf::RenderWindow& window);
};

class Level : public Input
{
	Block block = Block(10, 0, sf::Color::Blue);
	Block block2 = Block(10, 1, sf::Color::Blue);
	Spike spike = Spike(100, FLOOR, sf::Color::Red);
	Player player;
	sf::RectangleShape floor;

public:
	Level();
	~Level();

	void draw(sf::RenderWindow& window);
};

