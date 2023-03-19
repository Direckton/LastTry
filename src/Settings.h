#pragma once
#include "SFML/Graphics.hpp"
#include "InputHandler.h"

#define SLIDER_BOUNDS 200

class Settings : public Input, public Checkbox
{
private:
	sf::Text title, left, right;
	sf::Font font;
	sf::CircleShape circle;
	sf::RectangleShape bar ,progress;
	int width;

	bool sliderActive = false;
	
public:
	Settings(){}
	Settings(int _width, int _hight);
	~Settings();

	void draw(sf::RenderWindow& window);
	void changeCirclePosition(int x, int y, sf::RenderWindow& window);
	void checkForBounds();
	void activateSlider(sf::RenderWindow& window);
	void deactivateSlider();
	bool getSliderStatus();
};

class Slider
{
	//TODO move slider into this object
};

class Checkbox
{
protected:
	sf::RectangleShape box;
	bool check;
public:
	Checkbox(bool _check);
	~Checkbox() {};
	
	void draw(sf::RenderWindow& window);
};