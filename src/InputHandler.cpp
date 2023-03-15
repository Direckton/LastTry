#include "InputHandler.h"

int Input::keyHandler(sf::Event& event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
	{
		moveUp();
		return 0;
	}
	case sf::Keyboard::Down:
	{
		moveDown();
		return 0;

		break;
	}
	case sf::Keyboard::Left:
	{
		moveLeft();
		return 0;

		break;
	}
	case sf::Keyboard::Right:
	{
		return 0;

		break;
	}
	case sf::Keyboard::Enter:
	{
		select();	//create event that will acknowladge change of submenu
		//doesnt have to be inhirited method and is handled in update
		return 1;

		break;
	}
	case sf::Keyboard::Escape:
	{
		escape();
		return 2;
		break;
	}
	default:
		break;
	}
}