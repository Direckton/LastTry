#include "Music.h"

SoundControler::SoundControler()
{
	Fileloader file;
	auto data = file.getJson("res/json/settings.json");
	menuMusic.setVolume(file.getVolume(data,"music"));
	music.setVolume(file.getVolume(data,"music"));
	sfx.setVolume(file.getVolume(data,"sfx"));
	
}

SoundControler::~SoundControler()
{
}

void SoundControler::playMenuMusic()
{

	if (music.getStatus() == 2 )
	{
		music.stop();
	}
	if (menuMusic.getDuration() == sf::Time(sf::milliseconds(0)))
	{
		if (!menuMusic.openFromFile("res/sounds/Sweden.wav"))
		{
			std::cerr << "didnt load music" << std::endl;
		}
	}
	menuMusic.play();
}

void SoundControler::playMusic(std::string path)
{
	if (menuMusic.getStatus() == 2)
	{
		menuMusic.stop();
	}
	if (music.getDuration() == sf::Time(sf::milliseconds(0)))
	{
		if (!music.openFromFile(path))
		{
			std::cout << "Error while loading music from: " << path << std::endl;
		}
	}
	music.play();
	
}

void SoundControler::stopMusic()
{
	if (music.getDuration() != sf::Time(sf::milliseconds(0)))
	{
		music.stop();
		//music.~Music();
	}

}
void SoundControler::stopMenuMusic()
{
	if (menuMusic.getDuration() != sf::Time(sf::milliseconds(0)))
	{
		menuMusic.stop();
	}
}

void SoundControler::setMusicVolume(float volume)
{
	music.setVolume(volume);
}

float SoundControler::getMusicVolume()
{
	return music.getVolume();
}

void SoundControler::replayMusic()
{
	music.play();
}

void SoundControler::initSfx(std::string path)
{
	if (!buffer.loadFromFile(path))
	{
		std::cerr << "Error while loading music from: " << path << std::endl;
	}
	sfx.setBuffer(buffer);
}

void SoundControler::playSfx()
{
	sfx.play();
}