#include "LevelSelector.h"

Level::Level(int _width, int _height, std::string name)
{
	if (!font.loadFromFile("OXYGENE1.ttf"))
	{
		//error
	}
	label.setFont(font);
	label.setCharacterSize(60);
	label.setFillColor(sf::Color::White);
	label.setString(name);
	label.setPosition(_width / 2 - label.getGlobalBounds().width / 2, 20);

}

void Level::draw(sf::RenderWindow &window)
{
	window.draw(label);
}

Selector::Selector(int _width, int _height)
{
	width = _width;
	height = _height;
	for (int i = 0; i < 4; i++)
	{
		std::string name = "LEVEL " + std::to_string(i+1);
		level = new Level(_width+i*_width*1.5, _height,name);
		levels.push_back(level);
	}

	levelInFocus = 0;
	view.reset(sf::FloatRect(0, 0, _width, _height));
	switchLevel(++levelInFocus);
}


void Selector::draw(sf::RenderWindow& window)
{
	if (viewMoving)
	{
		view.move(sf::Vector2f(1, 0));
		if (view.getCenter() == sf::Vector2f(levelInFocus * width, height/2))
		{
			viewMoving = false;
		}
		std::cout << view.getCenter().x << std::endl;
	}
	window.setView(view);
	window.clear();
	//levels[0]->draw(window);
	for (auto l: levels)
	{
		l->draw(window);
	}
}

void Selector::switchLevel(int level)
{
	levelInFocus = level;
	viewMoving = true;
}