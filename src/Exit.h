#pragma once
#include "InputHandler.h"
#include "SFML/Graphics.hpp"

#define OPTIONS 2

class Exit : public Input
{
	sf::Text title, confirmation, cursor, options[OPTIONS];
	sf::Font font;
	int selector;
public:
	Exit(int width, int hight);
	~Exit(){}
	void draw(sf::RenderWindow& window);
	void moveLeft();
	void moveRight();
	int getSelector();
};