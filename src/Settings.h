#pragma once
#include "SFML/Graphics.hpp"
#include "InputHandler.h"

#define SLIDER_BOUNDS 200


class Checkbox
{
protected:
	sf::RectangleShape box;
	sf::Texture t_tick;
	sf::Image i_tick;
	sf::Sprite s_tick;

	bool check;
public:
	Checkbox() {}
	Checkbox(bool _check);
	~Checkbox() {};

	void draw(sf::RenderWindow& window);

	void setPosition(int x, int y);
};

class Settings : public Input, public Checkbox
{
private:
	sf::Text title, left, right;
	sf::Font font;
	sf::CircleShape circle;
	sf::RectangleShape bar ,progress;

	Checkbox checkbox1;
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
