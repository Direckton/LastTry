#pragma once
#include <SFML/Graphics.hpp>

class Level
{
private:
	sf::Text label;
	sf::Font font;
public:
	Level(){}
	Level(int _width, int _height);
	~Level(){}

	void draw(sf::RenderWindow& window);
};

class Selector
{
	Level *level;
	std::vector<Level *> levels;
public:
	Selector() {};
	Selector(int _width, int _height);

	void draw(sf::RenderWindow& window);
};