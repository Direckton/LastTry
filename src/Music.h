#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class SoundControler
{
	sf::Music menuMusic;
	sf::Music levelMusic;
	//sf::Sound sfx;
public:
	SoundControler();
	~SoundControler();
};