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
	//60x60px
	int x, y;

public:
	Block();
	~Block();
	void draw(sf::RenderWindow& window);
};

class Spike
{
	int x, y;
	sf::VertexArray triangle;
	sf::CircleShape tri;


public:
	Spike();
	Spike(int _x, int _y, sf::Color color);

	void draw(sf::RenderWindow& window);
};

class Level : public Input
{
	Block block;
	Spike spike;
	Player player;
	sf::RectangleShape floor;

public:
	Level();
	~Level();

	void draw(sf::RenderWindow& window);
};

