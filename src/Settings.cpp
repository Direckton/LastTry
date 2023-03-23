#include "Settings.h"


Settings::Settings(int _width, int _hight)
{	
	width = _width;
	for (int i = 0; i < 3; i++)
	{
		checkbox.push_back(Checkbox(ch));
	}
	for (int i = 0; i < 3; i++)
	{
		checkbox[i].setPosition(width / 3 * i + SLIDER_BOUNDS, 450);
	}
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

	progress.setSize(sf::Vector2f(circle.getPosition().x - SLIDER_BOUNDS, 10));
	progress.setFillColor(sf::Color(3, 252, 248,100));
	progress.setPosition(bar.getPosition());

	left.setFont(font);
	right.setFont(font);
}
Settings::~Settings()
{

}

void Settings::checkForBounds(sf::RenderWindow &window)
{
	for (int i = 0; i < 3; i++)
	{

		if (checkbox[i].getShape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))
			&& !changeState)
		{
			changeState = true;
			if (checkbox[i].getStatus())
			{
				checkbox[i].setStatus(false);

			}
			else
			{
				checkbox[i].setStatus(true);

			}
		}
	}
}

void Settings::activateSlider(sf::RenderWindow &window)
{
	//std::cout << circle.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) << std::endl;
	if (circle.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		sliderActive = true;
		
	}
	//sliderActive = false;
	
}


void Settings::deactivateClick()
{
	changeState = false;
}


void Settings::deactivateSlider()
{
	sliderActive = false;
}

bool Settings::getSliderStatus()
{
	return sliderActive;
}

void Settings::changeCirclePosition(int x, int y, sf::RenderWindow& window)
{

	//left.setFillColor(sf::Color::White);
	//left.setString(std::to_string(circle.getPosition().x));
	//left.setPosition(200, 500);

	//right.setFillColor(sf::Color::White);
	//right.setString(std::to_string(circle.getPosition().x+ circle.getGlobalBounds().width));
	//right.setPosition(1000, 500);
	//std::cout << circle.getPosition().x<< std::endl;
	if (x > SLIDER_BOUNDS && x < width - SLIDER_BOUNDS)
	{
		circle.setPosition(x, circle.getPosition().y);
		progress.setSize(sf::Vector2f(circle.getPosition().x - SLIDER_BOUNDS, 10));
	}
	//circle.getGlobalBounds()
}


void Settings::draw(sf::RenderWindow& window)
{
	window.clear();

	window.draw(left);
	window.draw(right);
	window.draw(bar);
	window.draw(progress);
	for (int i = 0; i < 3; i++)
	{
		checkbox[i].draw(window);

	}
	window.draw(title);
	window.draw(circle);
}

Checkbox::Checkbox()
{
	box.setSize(sf::Vector2f(25, 25));
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineThickness(3);
	box.setOutlineColor(sf::Color::White);

	if (!t_tick.loadFromFile("res/tick.png"))
	{
		std::cout << "Loding file did not succed" << std::endl;
	}
	t_tick.setSmooth(true);

	s_tick.setTexture(t_tick);
	s_tick.setScale(sf::Vector2f(0.07, 0.07));
	
}


void Checkbox::setSprite(sf::Texture& tx)
{
	s_tick.setTexture(tx);
}

void Checkbox::draw(sf::RenderWindow& window)
{
	window.draw(box);
	if (check)
	{
		window.draw(s_tick);

	}
}

void Checkbox::setPosition(int _x, int _y)
{
	box.setPosition(_x, _y);
	s_tick.setPosition(_x - TICK_OFFSET, _y - TICK_OFFSET);
}

void Checkbox::setStatus(bool state)
{
	check = state;
}
bool Checkbox::getStatus()
{
	return check;
}

sf::RectangleShape Checkbox::getShape()
{
	return box;
}