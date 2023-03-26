#include "Music.h"

SoundControler::SoundControler()
{
	if (!menuMusic.openFromFile("res/sounds/Sweden.wav"))
	{
		std::cout << "didnt load music" << std::endl;
	}
	
}

SoundControler::~SoundControler()
{

}

void SoundControler::playMenuMusic()
{
	if (menuMusic.getDuration() == sf::Time(sf::milliseconds(0)))
	{
		if (!menuMusic.openFromFile("res/sounds/Sweden.wav"))
		{
			std::cout << "didnt load music" << std::endl;
		}
	}
	menuMusic.play();
}

void SoundControler::playMusic(std::string path)
{
	music = new sf::Music;
	if (music->getDuration() == sf::Time(sf::milliseconds(0)))
	{
		if (!music->openFromFile(path))
		{
			std::cout << "Error while loading music from: " << path << std::endl;
		}
	}
	music->play();
	
}

void SoundControler::stopMusic()
{
	if (music->getDuration() != sf::Time(sf::milliseconds(0)))
	{
		music->stop();
		music->~Music();
	}

}

void SoundControler::setMusicVolume(float volume)
{
	music->setVolume(volume);
}

float SoundControler::getMusicVolume()
{
	return music->getVolume();
}
