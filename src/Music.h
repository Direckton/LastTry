#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include "FileLoader.h"

enum Selectors {
	musicSel, sfxSel
};

/**Class responsible for every sound and managing them*/
class SoundControler
{
	/**Main menu soundtrack*/
	sf::Music menuMusic;	
	sf::Music music;		/**Level soundtrack*/
	sf::Sound sfx;			/**Variable for sound effects*/
	sf::SoundBuffer buffer;	/**Buffer for loading SFX to memory*/
public:
	SoundControler();
	~SoundControler();
	/**Initializes soundtrack, stops level music on condition it was playing*/
	void playMenuMusic();	
	/**self explanotary*/
	void stopMenuMusic();	
	/**loads and plays music from specified path*/
	void playMusic(std::string path);	
	/**self explanotary*/
	void stopMusic();		
	/**Sets volume based on parameters and selectors i.e. look above for Selectors enum*/
	void setVolume(float volume, Selectors selector);	
	/**returns volume in range 0-100*/
	float getMusicVolume();	
	/**restarts current track, must bes topped first by stopMusic()*/
	void replayMusic();		
	/**Initializes sound effects, loads it into buffer and assigns it into sf::Sound, doesn't play it*/
	void initSfx(std::string path);	
	/**Plays SFX once*/
	void playSfx();	
};