#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"

class LevelInstance 
{
private:
	sf::Text label, button, cursor;
	sf::Font font;
	int width, height;
public:
	LevelInstance(){}
	LevelInstance(int _width, int _height, int _offset, std::string name);
	~LevelInstance(){}

	void draw(sf::RenderWindow& window);
	int getCenter();
};

class Selector : public Input
{
	LevelInstance *level;
	std::vector<LevelInstance *> levels;
	sf::View view;
	unsigned levelInFocus;
	bool viewMovingRight = false, viewMovingLeft = false;
	int width, height;


public:
	Selector() {};
	Selector(int _width, int _height);

	void draw(sf::RenderWindow& window);

	void switchLevel(int level, bool right, bool left);
	void moveRight();
	void moveLeft();
	void select();
};