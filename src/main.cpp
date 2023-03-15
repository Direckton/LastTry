#include "SFML/Graphics.hpp"
#include "InputHandler.h"
#include "Menu.h"
#include "InterfaceController.h"
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720

using namespace sf;



int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "GeometryDash");
    Event event;
    InterfaceController controller(WIDTH,HEIGHT);


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
            case sf::Event::MouseMoved:
            {
                //might tank preformence
                controller.mouseInput(event);
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

        //Render
        controller.render(window);
        window.display();
	}

    return 0;
}