#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "FileLoader.h"
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

/**Class implementing single instance shown in LevelSelector*/
class LevelInstance 
{
private:
	sf::Text label, button, cursor, highscore;
	sf::Font font;
	int width, height;
public:
	LevelInstance() {}
	/**Constructor
	offset is how far right this instance is shifted in px*/
	LevelInstance(int _width, int _height, int _offset, std::string name);
	~LevelInstance(){}
	/**Draws single instance */
	void draw(sf::RenderWindow& window);
	/**Returns x coordinate of the center of this instance*/
	int getCenter();
};
/**Level Selector interface class
This class takes vector of levels based on their name
The name HAS TO BE IN UPPERCASE, it is a used font requirement*/
class Selector : public Input
{
	LevelInstance *level;
	std::vector<LevelInstance *> levels;
	std::vector<std::string> levelNames;
	sf::View view;
	unsigned levelInFocus;
	bool viewMovingRight = false, viewMovingLeft = false;
	int width, height;


public:
	Selector() {};
	Selector(int _width, int _height);

	/**Draws Level Selector interface and calls each level draw() methode*/
	void draw(sf::RenderWindow& window);
	/** Moves the view in specified direction creating sliding effect*/
	void switchLevel(int level, bool right, bool left);
	/**Navigation*/
	void moveRight();
	/**Navigation*/
	void moveLeft();
	/**Self explanotary*/
	std::string getLevelName();
};