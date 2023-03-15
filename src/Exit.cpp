#include "Exit.h"

Exit::Exit(int width, int height)
{
	selector = 1;
	if (!font.loadFromFile("OXYGENE1.ttf"))
	{
		std::cout << "Error while loading font!";
	}
	title.setFont(font);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(60);
	title.setString("EXIT");
	//title.setPosition(width / 2 - title.getGlobalBounds().width / 2, 20);
	title.setPosition(width/2 - title.getGlobalBounds().width/2, 20);

	confirmation.setFont(font);
	confirmation.setFillColor(sf::Color::White);
	confirmation.setCharacterSize(40);
	confirmation.setString("ARE YOU SURE YOU WANT TO EXIT?");
	confirmation.setPosition(width / 2 - confirmation.getGlobalBounds().width / 2, 120);

	options[0].setFont(font);
	options[0].setFillColor(sf::Color::White);
	options[0].setCharacterSize(40);

	options[0].setString("YES");
	options[0].setPosition(width / 3 - options[0].getGlobalBounds().width / 2, 200); options[0].setFont(font);
	
	options[1].setFont(font);
	options[1].setFillColor(sf::Color::White);
	options[1].setCharacterSize(40);
	options[1].setString("NO");
	options[1].setPosition(width *(2.0/3.0) - options[1].getGlobalBounds().width / 2, 200);

	cursor.setFont(font);
	cursor.setScale(1.5, 1.5);
	cursor.setFillColor(sf::Color::White);
	cursor.setString("m");
	cursor.setRotation(90);
	cursor.setPosition(sf::Vector2f(options[selector].getGlobalBounds().left, options[selector].getPosition().y+10));

}

void Exit::draw(sf::RenderWindow& window)
{
	//title.setString(std::to_string(selector));
	window.clear();

	window.draw(title);
	window.draw(cursor);
	window.draw(confirmation);
	for (int i = 0; i < OPTIONS; i++)
	{
		window.draw(options[i]);
	}
}

void Exit::moveLeft()
{
	if (selector > 0)
	{
		selector--;
		cursor.setPosition(sf::Vector2f(options[selector].getGlobalBounds().left, options[selector].getPosition().y + 10));

	}
}

void Exit::moveRight()
{
	if (selector < OPTIONS-1)
	{
		selector++;
		cursor.setPosition(sf::Vector2f(options[selector].getGlobalBounds().left, options[selector].getPosition().y + 10));

	}
}

int Exit::getSelector()
{
	return selector;
}