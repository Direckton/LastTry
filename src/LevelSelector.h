#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"

class Level 
{
private:
	sf::Text label;
	sf::Font font;
public:
	Level(){}
	Level(int _width, int _height, std::string name);
	~Level(){}

	void draw(sf::RenderWindow& window);
};

class Selector : public Input
{
	Level *level;
	std::vector<Level *> levels;
	sf::View view;
	unsigned levelInFocus;
	bool viewMoving = false;
	int width, height;

public:
	Selector() {};
	Selector(int _width, int _height);

	void draw(sf::RenderWindow& window);

	void switchLevel(int level);
};