#pragma once
#include "SFML/Window.hpp"
#include <iostream>

/**Sort of a controller in strategy design pattern*/
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
	virtual void space() {}

	/**Calls correct overriden virtual method in currently active menu*/
	int keyHandler(sf::Event& event);
	
};