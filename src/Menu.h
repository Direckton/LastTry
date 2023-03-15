#pragma once
#include "SFML/Graphics.hpp"
#include "InputHandler.h"

#define MENU_ELEMENTS 3

class Menu : public Input
{
	sf::Text title, cursor, elements[MENU_ELEMENTS];
	sf::Font font;
	int selector; // currently selected item in menu
	int width, height; //h&w of the screen
public:
	Menu(){}
	Menu(int _width, int _height);
	void moveUp();
	void moveDown();
	int getSelector();
	void draw(sf::RenderWindow& window);
};