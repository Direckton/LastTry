#pragma once
#include "SFML/Window.hpp"
#include <iostream>

class Input
{
public:
	Input() {}
	~Input() {}

	virtual void moveUp() {}
	virtual void moveDown() {}
	virtual void moveRight() {}
	virtual void moveLeft() {}
	virtual void select() {}
	virtual void escape() {}

	int keyHandler(sf::Event& event);
	
};