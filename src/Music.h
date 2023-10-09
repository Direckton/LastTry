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
	sf::Music menuMusic;	//Main menu soundtrack
	sf::Music music;		//Level soundtrack
	sf::Sound sfx;			//Variable for sound effects
	sf::SoundBuffer buffer;	//Buffer for loading SFX to memory
public:
	SoundControler();
	~SoundControler();
	void playMenuMusic();	//Initializes soundtrack, stops level music on condition it was playing
	void stopMenuMusic();	//self explanotary
	void playMusic(std::string path);	//loads and plays music from specified path
	void stopMusic();		//self explanotary
	void setVolume(float volume, Selectors selector);	//Sets volume based on parameters and selectors i.e. look above for Selectors enum
	float getMusicVolume();	//returns volume in range 0-100
	void replayMusic();		//restarts current track, must bes topped first by stopMusic()
	void initSfx(std::string path);	//Initializes sound effects, loads it into buffer and assigns it into sf::Sound, doesn't play it
	void playSfx();	//Plays SFX once
};