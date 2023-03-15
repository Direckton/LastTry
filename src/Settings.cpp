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



}
Settings::~Settings()
{

}


void Settings::draw(sf::RenderWindow& window)
{
	window.clear();

	window.draw(title);
}