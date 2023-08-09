#include "LevelSelector.h"

LevelInstance::LevelInstance(int _width, int _height, int _offset, std::string name)
{
	width = _width;
	height = _height;
	if (!font.loadFromFile("OXYGENE1.ttf"))
	{
		//error
	}
	label.setFont(font);
	label.setCharacterSize(60);
	label.setFillColor(sf::Color::White);
	label.setString(name);
	label.setPosition(width / 2 - label.getGlobalBounds().width / 2 + _offset, 20);

	button.setFont(font);
	button.setCharacterSize(100);
	button.setFillColor(sf::Color::White);
	button.setString("PLAY");
	button.setPosition(width / 2 - label.getGlobalBounds().width / 2 + _offset, 360-button.getGlobalBounds().height/2);

	cursor.setFont(font);
	cursor.setCharacterSize(100);
	cursor.setFillColor(sf::Color::White);
	cursor.setString("m");
	cursor.setRotation(90);
	cursor.setPosition(sf::Vector2f(button.getGlobalBounds().left, 
		button.getPosition().y + button.getGlobalBounds().height/2));

}

void LevelInstance::draw(sf::RenderWindow &window)
{
	window.draw(label);
	window.draw(button);
	window.draw(cursor);
}

int LevelInstance::getCenter()
{
	return label.getPosition().x + label.getGlobalBounds().width/2;
}

Selector::Selector(int _width, int _height)
{
	width = _width;
	height = _height;

	int i = 0;
	const fs::path levelPath{ "res/json/level" };
	for (auto const& dir_entry : std::filesystem::directory_iterator{ levelPath })
	{
		std::string name = dir_entry.path().stem().string();
		levelNames.push_back(dir_entry.path().filename().string());
		level = new LevelInstance(width, _height, i*width ,name);
		levels.push_back(level);
		i++;
	}


	levelInFocus = 0;
	view.reset(sf::FloatRect(0, 0, _width, _height));
	//switchLevel(++levelInFocus);
}


void Selector::draw(sf::RenderWindow& window)
{
	if (viewMovingRight)
	{
		view.move(sf::Vector2f(30, 0));
		if (view.getCenter().x >= levels[levelInFocus]->getCenter())
		{
			viewMovingRight = false;
		}
		//		std::cout << levelInFocus << std::endl;
	}	
	if (viewMovingLeft)
	{
		view.move(sf::Vector2f(-30, 0));
		if (view.getCenter().x <= levels[levelInFocus]->getCenter())
		{
			viewMovingLeft = false;
		}
		//		std::cout << levelInFocus << std::endl;
	}
	window.setView(view);
	window.clear();
	//levels[0]->draw(window);
	for (auto l: levels)
	{
		l->draw(window);
	}
}

void Selector::switchLevel(int level, bool right, bool left)
{
	levelInFocus = level;
	viewMovingRight = right;
	viewMovingLeft = left;
}

void Selector::moveRight()
{
	if (levelInFocus < levels.size() - 1)
	{
		levelInFocus++;
		this->switchLevel(levelInFocus, true, false);
	}
}
void Selector::moveLeft()
{
	if (levelInFocus > 0)
	{
		levelInFocus--;
		this->switchLevel(levelInFocus, false, true);
	}
}

void Selector::select()
{

	//spawn level
	//levele itself handles fileloading
}

std::string Selector::getLevelName()
{
	return levelNames[levelInFocus];
}