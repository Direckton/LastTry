#include "SFML/Graphics.hpp"
#include "InputHandler.h"
#include "Menu.h"
#include "InterfaceController.h"
#include "Music.h"
#include <iostream>
#include "FileLoader.h"
#include "Level.h"


#include <SFML/Audio.hpp>

#define WIDTH 1280
#define HEIGHT 720

using namespace sf;

/**Setup of baseline parameters and main SFML loop and event handling*/
int main()
{

    ContextSettings CSettings;
    CSettings.antialiasingLevel = 8;

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "GeometryDash",sf::Style::Default,CSettings);
    View view;
    Event event;
    InterfaceController controller(WIDTH,HEIGHT);    

    view.reset(sf::FloatRect(0, 0, WIDTH, HEIGHT));

    view.getCenter();
    window.setView(view);

    window.getSettings().antialiasingLevel;
    window.setFramerateLimit(120);

    sf::Font font;
    sf::Text title;

    if (!font.loadFromFile("OXYGENE1.ttf"))
    {
        std::cout << "Error while loading font!";
    }
    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setCharacterSize(60);
    
    bool mouseTrack = false;

    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;

	while (window.isOpen())
	{
        begin = std::chrono::high_resolution_clock::now();
        //Handle events
         while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window.close();
                break;

            }
            case sf::Event::KeyPressed:
            {
                controller.input(event);
                break;

            }
            case sf::Event::MouseButtonPressed:
            {
                mouseTrack = true;
                //might tank preformence
                
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                mouseTrack = false;
                controller.mouseDeactivate();
                //might tank preformence
                
                break;
            }
            default:
                break;
            }
            
        }


        //Update
        if (controller.getClose())
        {
            //TODO closing procedure: saving progress etc and replace close()
            window.close();
        }

        if (mouseTrack)
        {
            controller.mouseInput(event, window);
        }
        
        //Render

        controller.render(window);
    /*    int fps = 120;
        end = std::chrono::high_resolution_clock::now();
        auto nTime = end - begin;
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(nTime);
        if (time != std::chrono::milliseconds(0))
        {
             fps= std::chrono::milliseconds(1000) / time;
        }

        title.setString(std::to_string(fps));

        window.draw(title);*/
        //window.draw(sp);
        window.display();

	}

    return 0;
}