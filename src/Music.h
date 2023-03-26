#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class SoundControler
{
	sf::Music menuMusic;
	sf::Music *music;
	sf::Sound sfx;
public:
	SoundControler();
	~SoundControler();
	void playMenuMusic();
	void playMusic(std::string path);
	void stopMusic();
	void setMusicVolume(float volume);
	float getMusicVolume();
};