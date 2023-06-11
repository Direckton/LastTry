#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include <math.h>
#include <chrono>

#define GRID_WIDTH 60
#define GRID_HIGHT 60
#define FLOOR 600

class Player
{
	sf::Sprite sprite;
	sf::Texture texture;
	sf::FloatRect bb;
	int x, y;
	bool onGround = true;

	float pi = 3.14159265359f;
	float yDelta = 0;


public:
	Player();

	void draw(sf::RenderWindow& window);
	void jump();
	void update();
	sf::FloatRect getBounds();
	void reset();
	void setOnGround(int y);
	bool getOnGround();
};

class Block
{
	//sf::RectangleShape rectangle;
	sf::VertexArray block;
	sf::Sprite s;
	sf::Texture t;
	//60x60px
	int x, y;

public:
	Block(int x, int y, const sf::Color& color);
	~Block();
	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds();
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
	std::vector<Block> blocks;
	Block block1 = Block(9, 0, sf::Color::Blue);
	Block block2 = Block(10, 0, sf::Color::Blue);
	Spike spike = Spike(11, 0, sf::Color::Blue);
	Player player;
	sf::RectangleShape floor;

	sf::FloatRect lastPosition;

	bool eventQueue = false;
	std::chrono::milliseconds elapsed = std::chrono::milliseconds(200);
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;



public:
	Level();
	~Level();

	void draw(sf::RenderWindow& window);
	void space();
	void update();
};

