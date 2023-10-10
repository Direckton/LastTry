#pragma once
#include "InputHandler.h"
#include "SFML/Graphics.hpp"

#define OPTIONS 2
/**Exit interface class*/
class Exit : public Input
{
	sf::Text title, confirmation, cursor, options[OPTIONS];
	sf::Font font;
	int selector;
public:
	Exit(int width, int hight);
	~Exit(){}
	/**Draws exit interface*/
	void draw(sf::RenderWindow& window);
	/**Navigation*/
	void moveLeft();
	/**Navigation*/
	void moveRight();
	/**Returns currently slected item*/
	int getSelector();
};