#include "Settings.h"


Settings::Settings(int width, int hight)
{
	if (!font.loadFromFile("OXYGENE1.ttf"))
	{
		std::cout << "Error while loading font!";
	}
	title.setFont(font);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(60);
	title.setString("SETTINGS");
	title.setPosition(width / 2 - title.getGlobalBounds().width / 2, 20);
	
	circle.setRadius(15);
	circle.setPointCount(20);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineThickness(3);
	circle.setOutlineColor(sf::Color::White);
	circle.setPosition(0,0);
}
Settings::~Settings()
{

}

void Settings::changeCirclePosition(int x, int y)
{
	circle.setPosition(x, y);
}


void Settings::draw(sf::RenderWindow& window)
{
	window.clear();

	window.draw(title);
	window.draw(circle);
}