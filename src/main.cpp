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
    bool mouseTrack = false;

    //sf::Texture tx;
    //tx.loadFromFile("res/tick.png");
    //sf::Sprite sp;
    //sp.setTexture(tx);

	while (window.isOpen())
	{
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
        if (controller.updateClose())
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
        //window.draw(sp);
        window.display();
	}

    return 0;
}