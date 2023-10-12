#include "InterfaceController.h"

InterfaceController::InterfaceController(int _width, int _height)
{
	width = _width;
	height = _height;
	interface = 0;

	setVolume();

	soundController.playMenuMusic();

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
	{
		exit = new Exit(width, height);
		break;
	}
	case 3:
	{
		selector = new Selector(width, height);
		break;
	}
	}
}

void InterfaceController::setVolume()
{
	Fileloader file;
	auto data = file.getJson("res/json/settings.json");
	volume = file.getVolume(data, "music");
	sfxVolume = file.getVolume(data, "sfx");
	soundController.setVolume(volume, musicSel);
	soundController.setVolume(sfxVolume, sfxSel);
}

InterfaceController::~InterfaceController()
{
	delete menu;
	delete settings;
	delete exit;
}

void InterfaceController::parser(int condition)
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

void InterfaceController::handleCheckbox(int checkbox)
{
	switch (checkbox)
	{
	case 0:
	{
		if (settings->getCheckboxStatus(0))
		{
			volume = 0;
			sfxVolume = 0;
			soundController.setVolume(volume, musicSel);
			soundController.setVolume(sfxVolume, sfxSel);

		}
		else
		{
			volume = settings->getSliderVolume(0);
			sfxVolume = settings->getSliderVolume(1);
			soundController.setVolume(volume, musicSel);
			soundController.setVolume(sfxVolume, sfxSel);

		}
		//mute
		break;
	}
	case 1:
	{
		break;
		//automatic replay
		break;
	}
	case 2:
	{
		//progress bar
		break;
	}
	default:
		break;
	}
}

void InterfaceController::resetVolume()
{
	settings->setCheckboxStatus(0, false);
	volume = settings->getSliderVolume(0);
	sfxVolume = settings->getSliderVolume(1);
}

void InterfaceController::mouseInput(sf::Event& event, sf::RenderWindow& window)
{
	switch (interface)
	{
	case 1:
	{
		if ((settings->volSlider.activateSlider(window) || settings->volSlider.getSliderStatus()) && !settings->sfxSlider.getSliderStatus())
		{
			resetVolume();
			volume = settings->volSlider.changeCirclePosition(sf::Mouse::getPosition(window).x, event.mouseMove.y, window);
			soundController.setVolume(volume, musicSel);
		}
		if ((settings->sfxSlider.activateSlider(window) || settings->sfxSlider.getSliderStatus()) && !settings->volSlider.getSliderStatus())
		{
			resetVolume();
			settings->sfxSlider.changeCirclePosition(sf::Mouse::getPosition(window).x, event.mouseMove.y, window);
			soundController.setVolume(volume, sfxSel);
		}

		handleCheckbox(settings->checkForBounds(window));

		settings->updateInterface();
		break;
	}
	default:
		break;
	}
}

void InterfaceController::mouseDeactivate()
{
	switch (interface)
	{
	case 1:
	{
		settings->volSlider.deactivateSlider();
		settings->deactivateClick();
		settings->sfxSlider.deactivateSlider();
		break;
	}
	default:
		break;
	}
}

void InterfaceController::input(sf::Event& event)
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
	case 3:
	{
		parser(selector->keyHandler(event));
		break;
	}
	case 4:
	{
		parser(level->keyHandler(event));
		break;
	}
	}
}

void InterfaceController::render(sf::RenderWindow& window)
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
	case 3:
	{
		selector->draw(window);
		break;
	}
	case 4:
	{
		level->draw(window);
		break;
	}
	}

}

void InterfaceController::menuSelection()
{
	switch (menu->getSelector())
	{
	case 0:
		//select level
		if (selector == nullptr)
		{
			selector = new Selector(width, height);
		}
		interface = 3;
		break;
	case 1:
	{
		//settings
		//delete menu;
		if (settings == nullptr)
		{
			settings = new Settings(width, height);
			settings->setCirclePosition(volume);
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

void InterfaceController::levelSelection()
{
	if (level == nullptr)
	{
		level = new Level((*selector).getLevelName()); //add level number through selector.getLevelIndex
		soundController.stopMenuMusic();
	}
	interface = 4;
}

bool InterfaceController::getClose()
{
	return close;
}

void InterfaceController::exitSelections()
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

void InterfaceController::select()
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
		//settings selection
		break;
	}
	case 2:
	{
		//exit selections
		exitSelections();
		break;

	}
	case 3:
	{
		levelSelection();
		break;
	}
	default:
		break;
	}
}

void InterfaceController::menuBack()
{
	//go to exit
	if (exit == nullptr)
	{
		exit = new Exit(width, height);
	}
	interface = 2;
}

void InterfaceController::goBackToMenu()
{
	if (settings != nullptr)
	{
		//save current status of volumes to file
		Fileloader file;
		auto data = file.getJson("res/json/settings.json");
		file.setVolume(data, "music", volume);
		file.setVolume(data, "sfx", sfxVolume);
		file.saveToFile(data, "res/json/settings.json");
		delete settings;
		settings = nullptr;
	}
	if (exit != nullptr)
	{
		delete exit;
		exit = nullptr;
	}
	if (selector != nullptr)
	{
		delete selector;
		selector = nullptr;
	}
	if (level != nullptr)
	{
		delete level;
		level = nullptr;
		soundController.playMenuMusic();
	}

	if (menu == nullptr)
	{
		menu = new Menu(width, height);
	}
	interface = 0;
}

void InterfaceController::back()
{
	//NO NEED TO DELETE CURRENT INTERFACE 
	//this is being handled later
	//totaly didnt look for it for a week
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
	case 3:
	{
		goBackToMenu();
		break;
	}
	case 4:
	{
		goBackToMenu();
		break;
	}
	default:
		break;
	}
}