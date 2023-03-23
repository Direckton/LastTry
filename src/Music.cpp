#include "Music.h"

SoundControler::SoundControler()
{
	if (!menuMusic.openFromFile("res/sounds/Sweden.wav"))
	{
		std::cout << "didnt load music" << std::endl;
	}
	menuMusic.play();
}

SoundControler::~SoundControler()
{

}