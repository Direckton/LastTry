#pragma once
#include "SFML/Graphics.hpp"
#include "InputHandler.h"

#define SLIDER_BOUNDS 200

#define TICK_OFFSET 10

/**Class for handling and drawing Chackboxes in setting menu*/
class Checkbox
{
protected:
	sf::Text title;
	sf::Font font;
	sf::RectangleShape box;
	sf::Texture t_tick;
	sf::Sprite s_tick;
	std::string name;

	/**Initial falue of chcckbox*/
	bool check = false;
public:
	Checkbox() {};
	Checkbox(std::string title);
	Checkbox(const Checkbox& _checkbox, std::string _name)
	{
		box = _checkbox.box;
		t_tick = _checkbox.t_tick;
		s_tick = _checkbox.s_tick;
		title = _checkbox.title;
		title.setString(_name);
	}
	~Checkbox() {};
	/**Draws single checkbox on a screen*/
	void draw(sf::RenderWindow& window);
	/**Changes checkbox state*/
	void setStatus(bool state);
	/**Self explanotary*/
	bool getStatus();
	/**Returns bounding box of chceckbox for detection when mouse is over it*/
	sf::RectangleShape getBounds();
	/**Self explanotary*/
	void setPosition(int x, int y);

};

/**Class for handling and drawing Sliders in setting menu*/
class Slider
{
protected:
	sf::CircleShape circle;
	sf::RectangleShape bar, progress;

	int width, height; //window size
	int x, y; //x and y coordinates of the slider
	int boundX, boundY; //max circle position

	bool sliderActive = false;

public:
	Slider() {};
	Slider(int _width, int _height, int _y);
	~Slider(){}

	/**Draws single slider on a screen*/
	void draw(sf::RenderWindow& window);
	/**Checks if mouse is in bounds, activates slider*/
	bool activateSlider(sf::RenderWindow& window);
	/**Changes position slider position, returns % of filled slider*/
	int changeCirclePosition(int x, int y, sf::RenderWindow& window);
	/**Self explanotary*/
	sf::Vector2f getCirclePosition();
	/**Returns wether slider is active or not*/
	bool getSliderStatus();
	/**Deactivates slider, the circle wont move anymore until it is activated again (changeCirclePosition() won't work)*/
	void deactivateSlider();
	/**Used for setting initial value based on variable*/
	void setCirclePosition(int volume);


};

/**Settings menu main Interface class, inherits Checkbox and Slider classes*/
class Settings : public Input, public Checkbox, public Slider
{
private:
	sf::Text title, volume;
	sf::Text volumeValue;
	sf::Font font;
	sf::CircleShape circle;
	sf::RectangleShape bar ,progress;

	Checkbox copy = Checkbox("");	//Copu constructor used to initailize checkboxes, could be a pointer

	Checkbox mute, replay, progressBar;

	std::vector<Checkbox> checkbox;

	int width;

	bool sliderActive = false;
	bool changeState = false;
	
public:
	
	Slider volSlider;
	Slider sfxSlider;

	Settings(){}
	Settings(int _width, int _hight);
	~Settings();
	/**Draws all elements of Settings class and calls inherited classes draw() methods*/
	void draw(sf::RenderWindow& window);
	/**Inherited method from Slider class*/
	int changeCirclePosition(int x, int y, sf::RenderWindow& window);
	/**Checks whether the mouse is in bounding box of the slider*/
	int checkForBounds(sf::RenderWindow& window);
	/**Inherited method from Slider class*/
	bool activateSlider(sf::RenderWindow& window);
	/**Inherited method from Slider class*/
	void deactivateSlider();
	/**Inherited method from Slider class*/
	bool getSliderStatus();
	/**Sets flag to false for mouse activation*/
	void deactivateClick();
	/**Returns checkbox state*/
	bool getCheckboxStatus(int i);
	/**Sets checkbox state*/
	void setCheckboxStatus(int i, bool state);
	/**Inherited method from Slider class*/
	sf::Vector2f getCirclePosition();
	/**Updates Volume value of in the interface*/
	void updateInterface();

	
	/**
	* calculates volume out of slider position from 0 to 100
	* Returns
	* 0 for music volume
	* 1 for sfx volume
	*/
	int getSliderVolume(int silder);

};

