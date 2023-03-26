#pragma once
#include "SFML/Graphics.hpp"
#include "InputHandler.h"

#define SLIDER_BOUNDS 200

#define TICK_OFFSET 10


class Checkbox
{
protected:
	sf::RectangleShape box;
	sf::Texture t_tick;
	sf::Sprite s_tick;


	bool check = true;
public:
	Checkbox();
	Checkbox(const Checkbox& _checkbox)
	{
		box = _checkbox.box;
		t_tick = _checkbox.t_tick;
		s_tick = _checkbox.s_tick;
	}
	~Checkbox() {};

	void draw(sf::RenderWindow& window);
	void setSprite(sf::Texture& tx);
	void setStatus(bool state);
	bool getStatus();

	sf::RectangleShape getShape();
	void setPosition(int x, int y);
};

class Settings : public Input, public Checkbox
{
private:
	sf::Text title, left, right, volume, volumeValue;
	sf::Font font;
	sf::CircleShape circle;
	sf::RectangleShape bar ,progress;

	Checkbox ch;

	std::vector<Checkbox> checkbox;
	int width;

	bool sliderActive = false;
	bool changeState = false;
	
public:
	Settings(){}
	Settings(int _width, int _hight);
	~Settings();

	void draw(sf::RenderWindow& window);
	int changeCirclePosition(int x, int y, sf::RenderWindow& window);
	void checkForBounds(sf::RenderWindow& window);
	void activateSlider(sf::RenderWindow& window);
	void deactivateSlider();
	bool getSliderStatus();
	void deactivateClick();


};

class Slider
{
	//TODO move slider into this object
};
