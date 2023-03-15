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
    RectangleShape shape(Vector2f(100,100));
    Event event;
    InterfaceController controller(WIDTH,HEIGHT);

    shape.setFillColor(Color::Magenta);

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
            default:
                break;
            }
            
        }

        //Update


        //Render
        controller.render(window);
        window.display();
	}

    return 0;
}