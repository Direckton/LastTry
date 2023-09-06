#include "Settings.h"


Settings::Settings(int _width, int _hight)
{	
	width = _width;
	height = _hight;


	mute = Checkbox(copy, "MUTE");
	replay = Checkbox(copy, "AUTO-REPLAY");
	progressBar = Checkbox(copy, "PROGRESS BAR");
	

	mute.setPosition(SLIDER_BOUNDS, 600);
	replay.setPosition(width/2-200, 600);
	progressBar.setPosition(width -500, 600);
	
	checkbox.push_back(mute);
	checkbox.push_back(replay);
	checkbox.push_back(progressBar);
	
	sfxSlider = Slider(_width, _hight, 300);
	volSlider = Slider(_width, _hight, 200);

	if (!font.loadFromFile("OXYGENE1.ttf"))
	{
		std::cout << "Error while loading font!";
	}
	title.setFont(font);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(60);
	title.setString("SETTINGS");
	title.setPosition(width / 2 - title.getGlobalBounds().width / 2, 20);

	volume.setFont(font);
	volume.setFillColor(sf::Color::White);
	volume.setCharacterSize(40);
	volume.setString("VOLUME: ");
	volume.setPosition(width / 2 - volume.getGlobalBounds().width / 2, 100);

	volumeValue.setFont(font);
	volumeValue.setFillColor(sf::Color::White);
	volumeValue.setCharacterSize(40);
	volumeValue.setString("50");
	volumeValue.setPosition(volume.getPosition().x + volume.getGlobalBounds().width, 100);

}
Settings::~Settings()
{

}

bool Settings::getCheckboxStatus(int i)
{
	return checkbox[i].getStatus();
}
void Settings::setCheckboxStatus(int i, bool state)
{
	checkbox[i].setStatus(state);
}

int Settings::checkForBounds(sf::RenderWindow &window)
{
	for (int i = 0; i < 3; i++)
	{
		if (checkbox[i].getShape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))
			&& !changeState)
		{
			changeState = true;
			if (checkbox[i].getStatus())
			{
				checkbox[i].setStatus(false);
			}
			else
			{
				checkbox[i].setStatus(true);
			}
			return i;
		}
	}
	return -1;
}


void Settings::deactivateClick()
{
	changeState = false;
}

void Settings::updateInterface()
{
	//int volume = (circle.getPosition().x - zero) / (bar.getSize().x - 5) * 100;
	int volume = (volSlider.getCirclePosition().x - SLIDER_BOUNDS) / (width - 2 * SLIDER_BOUNDS - 5) * 100;
	volumeValue.setString(std::to_string(volume));
}


int Settings::getSliderVolume(int slider)
{
	switch (slider)
	{
	case 0:
	{
		return (volSlider.getCirclePosition().x - SLIDER_BOUNDS) / (width - 2 * SLIDER_BOUNDS - 5) * 100;
	}
	case 1:
	{
		return (sfxSlider.getCirclePosition().x - SLIDER_BOUNDS) / (width - 2 * SLIDER_BOUNDS - 5) * 100;
	}
	default:
		return 50;
		break;
	}
}

void Settings::draw(sf::RenderWindow& window)
{
	window.clear();

	window.draw(volume);
	window.draw(volumeValue);
	volSlider.draw(window);
	sfxSlider.draw(window);
	/*mute.draw(window);
	replay.draw(window);
	progressBar.draw(window);*/
	for (int i = 0; i < 3; i++)
	{
		checkbox[i].draw(window);

	}
	window.draw(title);
	window.draw(circle);
}

Checkbox::Checkbox(std::string name)
{
	box.setSize(sf::Vector2f(25, 25));
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineThickness(3);
	box.setOutlineColor(sf::Color::White);

	if (!t_tick.loadFromFile("res/tick.png"))
	{
		std::cout << "Loding file did not succed" << std::endl;
	}
	t_tick.setSmooth(true);

	s_tick.setTexture(t_tick);
	s_tick.setScale(sf::Vector2f(0.07, 0.07));

	if (!font.loadFromFile("OXYGENE1.ttf"))
	{
		std::cout << "Error while loading font!";
	}
	title.setFont(font);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(40);
	title.setString(name);

	
}




void Checkbox::setSprite(sf::Texture& tx)
{
	s_tick.setTexture(tx);
}

void Checkbox::draw(sf::RenderWindow& window)
{
	window.draw(box);
	if (check)
	{
		window.draw(s_tick);
	}
	window.draw(title);
}

void Checkbox::setPosition(int _x, int _y)
{
	box.setPosition(_x, _y);
	s_tick.setPosition(_x - TICK_OFFSET, _y - TICK_OFFSET);
	title.setPosition(_x +50, _y-15);
}

void Checkbox::setStatus(bool state)
{
	check = state;
}
bool Checkbox::getStatus()
{
	return check;
}

sf::RectangleShape Checkbox::getShape()
{
	return box;
}


Slider::Slider(int _width, int _height, int _y)
{
	width = _width;
	height = _height;
	y = _y;
	bar.setSize(sf::Vector2f(width - 2 * SLIDER_BOUNDS, 10));
	bar.setFillColor(sf::Color::White);
	bar.setPosition(SLIDER_BOUNDS, y);

	boundX = bar.getSize().x;
	boundY = bar.getSize().y;

	circle.setRadius(15);
	circle.setPointCount(20);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineThickness(3);
	circle.setOutlineColor(sf::Color::White);
	circle.setPosition(width / 2, y);
	circle.setOrigin(circle.getRadius() / 2, circle.getRadius() / 2);

	progress.setSize(sf::Vector2f(circle.getPosition().x - SLIDER_BOUNDS, 10));
	progress.setFillColor(sf::Color(3, 252, 248, 100));
	progress.setPosition(bar.getPosition());
}

bool Slider::activateSlider(sf::RenderWindow& window)
{
	//std::cout << circle.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) << std::endl;
	if (bar.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		sliderActive = true;
		return true;
	}
	//sliderActive = false;
	return false;
}
void Slider::deactivateSlider()
{
	sliderActive = false;
}

bool Slider::getSliderStatus()
{
	return sliderActive;
}

sf::Vector2f Slider::getCirclePosition()
{
	return circle.getPosition();
}

int Slider::changeCirclePosition(int x, int y, sf::RenderWindow& window)
{

	int zero = SLIDER_BOUNDS;
	int full = width - SLIDER_BOUNDS;
	int volume = (circle.getPosition().x - zero) / (bar.getSize().x - 5) * 100;

	if (x > SLIDER_BOUNDS && x < full)
	{
		circle.setPosition(x, circle.getPosition().y);
		progress.setSize(sf::Vector2f(circle.getPosition().x - SLIDER_BOUNDS, 10));
		volume = (circle.getPosition().x - zero) / (bar.getSize().x - 5) * 100;
		
	}

	return volume;
}

void Slider::setCirclePosition(int volume)
{
	int zero = SLIDER_BOUNDS;
	int full = 1280 - SLIDER_BOUNDS;
	//int volume = (circle.getPosition().x - zero) / (bar.getSize().x - 5) * 100;
	float xCoordinates =full * (volume / 100.f);


	if (xCoordinates > SLIDER_BOUNDS && xCoordinates < full)
	{
		circle.setPosition(xCoordinates, circle.getPosition().y);
		progress.setSize(sf::Vector2f(circle.getPosition().x - SLIDER_BOUNDS, 10));
	}

}

void Slider::draw(sf::RenderWindow &window)
{
	window.draw(bar);
	window.draw(progress);
	window.draw(circle);
}