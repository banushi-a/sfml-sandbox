#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "eventHandlers.h"
#include "physicsHandlers.h"
#include <iostream>

#define PIXEL_SIZE 20
#define SCREEN_SIZE 50
#define TICK_RESET 120

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(PIXEL_SIZE * SCREEN_SIZE, PIXEL_SIZE * SCREEN_SIZE),
        "Sandbox Test");

    // Dynamic allocation of a 2D array (matrix)
    int **data = new int *[SCREEN_SIZE];
    for (int i = 0; i < SCREEN_SIZE; ++i)
    {
        data[i] = new int[SCREEN_SIZE];
    }

    int tick = 0;

    // Main Loop of The Program
    while (window.isOpen())
    {
        tick = (tick + 1) % TICK_RESET;
        // Poll all events on this tick
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Quit the application if the window is closed
            if (event.type == sf::Event::Closed)
                window.close();
            handleEvents(event);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tick == 0)
        {
            // Get the position where the mouse was clicked
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Calculate which cell we are in
            int row = ((int)mousePosition.y) / PIXEL_SIZE;
            int col = ((int)mousePosition.x) / PIXEL_SIZE;

            data[row][col] = (data[row][col] + 1) % 2;
        }

        // Make the bricks "fall"
        if (tick == 0)
        {
            updateData(data, SCREEN_SIZE);
        }

        // Clear the window and draw everything over
        if (tick == 0)
        {
            window.clear();
            for (int i = 0; i < SCREEN_SIZE; ++i)
            {
                for (int j = 0; j < SCREEN_SIZE; ++j)
                {
                    if (data[i][j])
                    {
                        sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                        shape.setFillColor(sf::Color(77, 26, 30));
                        shape.setPosition(sf::Vector2f(PIXEL_SIZE * j, PIXEL_SIZE * i));
                        window.draw(shape);
                    }
                }
            }
            window.display();
        }
    }

    return 0;
}
