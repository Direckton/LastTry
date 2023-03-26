#pragma once
#include "InputHandler.h"
#include "Menu.h"
#include "Settings.h"
#include "Exit.h"
#include <iostream>

class InterfaceController : public Menu, public Settings, public Input
{
	int interface; //0 = menu, 1 = settings
	Menu* menu = nullptr;
	Settings* settings = nullptr;
	Exit* exit = nullptr;

	int width, height; //h&w of the screen

	int volume;



	bool close = false;

public:
	InterfaceController(int _width, int _height)
	{
		width = _width;
		height = _height;
		interface = 0;


		switch (interface)
		{
		case 0:
		{
			menu = new Menu(width, height);
			break;
		}
		case 1:
		{
			settings = new Settings(width, height);
			break;
		}
		case 2:
			exit = new Exit(width, height);
			break;
		}
	}
	~InterfaceController()
	{
		delete menu;
		delete settings;
		delete exit;
	}

	void parser(int condition) //if key is associated with selecting it will return true
		//and so the interface change will be handled, else the normal key input will be prefomed
	{
		switch (condition)
		{
		case 0:
		{
			return;
		}
		case 1:
		{
			this->select();
			break;
		}
		case 2:
		{
			this->back();
			break;
		}
		default:
			break;
		}
	}

	void mouseInput(sf::Event& event, sf::RenderWindow &window)
	{
		switch (interface)
		{
		case 1:
		{
			if (!settings->getSliderStatus())
			{
				settings->activateSlider(window);
			}
			if(settings->getSliderStatus())
			{
				//std::cout << event.mouseMove.x << " " << event.mouseMove.y << std::endl;
				volume = settings->changeCirclePosition(event.mouseMove.x, event.mouseMove.y, window);

			}
			settings->checkForBounds(window);

			break;
		}
		default:
			break;
		}
	}
	
	int updateVolume()
	{
		return volume;
	}

	void mouseDeactivate()
	{
		switch (interface)
		{
		case 1:
		{
			settings->deactivateSlider();
			settings->deactivateClick();
			break;
		}
		default:
			break;
		}
	}
	
	void input(sf::Event & event)
	{
		switch (interface)
		{
		case 0:
		{
			parser(menu->keyHandler(event));
			break;
		}
		case 1:
		{
			parser(settings->keyHandler(event));
			break;
		}
		case 2:
		{
			parser(exit->keyHandler(event));
			break;
		}
		}
	}

	void render(sf::RenderWindow &window)
	{
		switch (interface)
		{
		case 0:
		{
			menu->draw(window);
			break;
		}
		case 1:
		{
			settings->draw(window);
			break;
		}
		case 2:
		{
			exit->draw(window);
			break;
		}
		}
	}
	void menuSelection()
	{
		switch (menu->getSelector())
		{
		case 0:
			//select level
			break;
		case 1:
		{
			//settings
			//delete menu;
			if (settings == nullptr)
			{
				settings = new Settings(width, height);
			}
			interface = 1;
			break;
		}
		case 2:
		{
			//exit prompt
			if (exit == nullptr)
			{
				exit = new Exit(width, height);
			}
			interface = 2;
			break;
		}
		default:
			break;
		}
	}

	bool updateClose()
	{
		return close;
	}

	void exitSelections()
	{
		switch (exit->getSelector())
		{
		case 0:
		{
			close = true;
			break;
		}
		case 1:
		{
			interface = 0;

			break;
		}
		default:
			break;
		}
	}

	void select()
	{
		switch (interface)
		{
		case 0:
		{
			menuSelection();
			break;
		}
		case 1:
		{
			//setting selections
			break;
		}
		case 2:
		{
			//exit selections
			exitSelections();

		}
		default:
			break;
		}
	}

	void menuBack()
	{
		//go to exit
		if (exit == nullptr)
		{
			exit = new Exit(width, height);
		}
		interface = 2;

	}

	void goBackToMenu()
	{
		//settings->menu
		//delete settings;
		if (menu == nullptr)
		{
			menu = new Menu(width, height);
		}
		interface = 0;
	}



	void back()
	{
		switch (interface)
		{
		case 0:
		{
			menuBack();
			break;
		}
		case 1:
		{
			goBackToMenu();
			break;

		}
		case 2:
		{
			goBackToMenu();
			break;
		}
		default:
			break;
		}
	}
};