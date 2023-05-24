#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	int x, y;
};

class Block
{
	//60x60px
	int x, y;

};

class Spike
{
	int x, y;

};

class Level
{
	sf::RectangleShape rectangle;

public:
	Level();
	~Level();

	void draw(sf::RenderWindow& window);
};

