#pragma once
#include "SFML/Graphics.hpp"
#include "InputHandler.h"


class Settings : public Input
{
private:
	sf::Text title;
	sf::Font font;
public:
	Settings(){}
	Settings(int _width, int _hight);
	~Settings();

	void draw(sf::RenderWindow& window);

};