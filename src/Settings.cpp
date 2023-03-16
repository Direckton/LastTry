#include "Settings.h"


Settings::Settings(int _width, int _hight)
{
	width = _width;
	if (!font.loadFromFile("OXYGENE1.ttf"))
	{
		std::cout << "Error while loading font!";
	}
	title.setFont(font);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(60);
	title.setString("SETTINGS");
	title.setPosition(width / 2 - title.getGlobalBounds().width / 2, 20);

	bar.setSize(sf::Vector2f(width - 2*SLIDER_BOUNDS,10));
	bar.setFillColor(sf::Color::White);
	bar.setPosition(SLIDER_BOUNDS, 200);


	
	circle.setRadius(15);
	circle.setPointCount(20);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineThickness(3);
	circle.setOutlineColor(sf::Color::White);
	circle.setPosition(width/2,200);
	circle.setOrigin(circle.getRadius() / 2, circle.getRadius() / 2);

	left.setFont(font);
	right.setFont(font);
}
Settings::~Settings()
{

}

void Settings::changeCirclePosition(int x, int y)
{

	left.setFillColor(sf::Color::White);
	left.setString(std::to_string(circle.getPosition().x));
	left.setPosition(200, 500);

	right.setFillColor(sf::Color::White);
	right.setString(std::to_string(circle.getPosition().x+ circle.getGlobalBounds().width));
	right.setPosition(1000, 500);
	std::cout << circle.getPosition().x<< std::endl;
	if (x > SLIDER_BOUNDS && x < width - SLIDER_BOUNDS)
	{
		if (x > circle.getPosition().x - circle.getRadius() &&
			x < circle.getPosition().x + circle.getGlobalBounds().width)
		{
			circle.setPosition(x, circle.getPosition().y);

		}

	}
	//circle.getGlobalBounds()
}


void Settings::draw(sf::RenderWindow& window)
{
	window.clear();

	window.draw(left);
	window.draw(right);
	window.draw(bar);

	window.draw(title);
	window.draw(circle);
}