#pragma once
#include "SFML/Graphics.hpp"
#include "InputHandler.h"

#define SLIDER_BOUNDS 200

class Settings : public Input
{
private:
	sf::Text title, left, right;
	sf::Font font;
	sf::CircleShape circle;
	sf::RectangleShape bar;
	int width;

	std::vector<sf::Vector2f> boundingBox;
	
public:
	Settings(){}
	Settings(int _width, int _hight);
	~Settings();

	void draw(sf::RenderWindow& window);
	void changeCirclePosition(int x, int y);
	void checkForBounds();

};