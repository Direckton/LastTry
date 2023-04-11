#include "LevelSelector.h"

Level::Level(int _width, int _height)
{
	if (!font.loadFromFile("OXYGENE1.ttf"))
	{
		//error
	}
	label.setFont(font);
	label.setCharacterSize(60);
	label.setFillColor(sf::Color::White);
	label.setString("LEVEL");
	label.setPosition(_width / 2 - label.getGlobalBounds().width / 2, 20);

}

void Level::draw(sf::RenderWindow &window)
{
	window.draw(label);
}

Selector::Selector(int _width, int _height)
{
	levels.push_back(Level(_width, _height));
}


void Selector::draw(sf::RenderWindow& window)
{
	for (auto l : levels)
	{
		l.draw(window);
	}
}