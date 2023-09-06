#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include "FileLoader.h"

enum Selectors {
	musicSel, sfxSel
};

class SoundControler
{
	sf::Music menuMusic;
	sf::Music music;
	sf::Sound sfx;
	sf::SoundBuffer buffer;
public:
	SoundControler();
	~SoundControler();
	void playMenuMusic();
	void stopMenuMusic();
	void playMusic(std::string path);
	void stopMusic();
	void setVolume(float volume, Selectors selector);
	float getMusicVolume();
	void replayMusic();
	void initSfx(std::string path);
	void playSfx();
};