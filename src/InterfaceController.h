#pragma once
#include "InputHandler.h"
#include "Menu.h"
#include "Settings.h"
#include "Exit.h"
#include "LevelSelector.h"
#include "Level.h"
#include "Music.h"
#include "FileLoader.h"
#include <iostream>

/**Class implementing Interface controlls and passing renderer priority*/
class InterfaceController : public Menu, public Settings, public Input, public Selector, public Level
{
	int interface; //0 = menu, 1 = settings
	Menu* menu = nullptr;
	Settings* settings = nullptr;
	Exit* exit = nullptr;
	Selector* selector = nullptr;
	Level* level = nullptr;

	SoundControler soundController;

	Fileloader file;

	int width, height; //h&w of the screen

	int volume = 50;
	int sfxVolume = 50;

	bool mute = false;

	bool close = false;

public:
	/**Sets up first scene to be loaded and displayed, based on interface variable*/
	InterfaceController(int _width, int _height);

	~InterfaceController();
	/**Fetches volume data from settings.json file*/
	void setVolume();
	/**Takes values
	0 do nothing
	1 call select() to navigate
	2 call back() to go back a menu*/
	void parser(int condition);
	/**Take action on checkboxes*/
	void handleCheckbox(int checkbox);
	/**Sets volumes to initial values*/
	void resetVolume();
	/**Implements mouse interaction*/
	void mouseInput(sf::Event& event, sf::RenderWindow& window);
	/**Calls methodes to deactivate mouse interaction*/
	void mouseDeactivate();
	/**Calls correct action based on selected interface and key pressed*/
	void input(sf::Event& event);
	/**Calls correct draw() methodes based on interface, drawing is handled by interface*/
	void render(sf::RenderWindow& window);
	/**Spawn correct scene based on selected item*/
	void menuSelection();
	/**Spawn correct level, pass controll, stop main menu soundtrack*/
	void levelSelection();
	/**Get flag used to close this program*/
	bool getClose();
	/**Handle Exit menu actions*/
	void exitSelections();
	/**Handle each menu selection items (navigation)*/
	void select();
	/**Pressing esc key in main menu causes displaying exit prompt, it's done here*/
	void menuBack();
	/**Return to main menu, delete current scene, if anny settings were changed, they are saved here*/
	void goBackToMenu();
	/**Call correct return method (navigation)*/
	void back();
};