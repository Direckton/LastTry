#include "Menu.h"

Menu::Menu(int _width, int _height)
{
	selector = 0;
	width = _width;
	height = _height;
	if (!font.loadFromFile("OXYGENE1.ttf"))
	{
		//handle error
	}

	title.setFont(font);
	title.setCharacterSize(60);
	title.setFillColor(sf::Color::White);
	title.setString("GEOMETRY DASH");
	title.setPosition(width / 2 - title.getGlobalBounds().width / 2, 20);


	elements[0].setFont(font);
	elements[0].setFillColor(sf::Color::White);
	elements[0].setString("SELECT LEVEL");
	elements[0].setPosition(width / 2 - elements[0].getGlobalBounds().width / 2, height / (MENU_ELEMENTS + 1) * 1);

	elements[1].setFont(font);
	elements[1].setFillColor(sf::Color::White);
	elements[1].setString("SETTINGS");
	elements[1].setPosition(width / 2 - elements[1].getGlobalBounds().width / 2, height / (MENU_ELEMENTS + 1) * 2);

	elements[2].setFont(font);
	elements[2].setFillColor(sf::Color::White);
	elements[2].setString("EXIT");
	elements[2].setPosition(width / 2 - elements[2].getGlobalBounds().width / 2, height / (MENU_ELEMENTS + 1) * 3);

	cursor.setFont(font);
	cursor.setScale(1.5, 1.5);
	cursor.setFillColor(sf::Color::White);
	cursor.setString("m");
	cursor.setRotation(90);
	cursor.setPosition(sf::Vector2f(elements[0].getGlobalBounds().left, elements[selector].getPosition().y));
}

void Menu::draw(sf::RenderWindow &window)
{
	//title.setString(std::to_string(selector));
	sf::View view(sf::FloatRect(0, 0, width, height)); //view reset form level and selector

	//view.move(sf::Vector2f(200, 0));

	window.setView(view);

	window.clear();

	window.draw(title);
	window.draw(cursor);
	for (int i = 0; i < MENU_ELEMENTS; i++)
	{
		window.draw(elements[i]);
	}
}

void Menu::moveDown()
{
	if (selector < MENU_ELEMENTS-1)
	{
		selector++; //yes i know i can increment in the line below bud R E A D A B I L I T Y
		cursor.setPosition(sf::Vector2f(elements[selector].getGlobalBounds().left, elements[selector].getPosition().y));
	}
}

void Menu::moveUp()
{
	if (selector > 0)
	{
		selector--; //yes i know i can increment in the line below bud R E A D A B I L I T Y
		cursor.setPosition(sf::Vector2f(elements[selector].getGlobalBounds().left, elements[selector].getPosition().y));
	}
}

int Menu::getSelector()
{
	return selector;
}