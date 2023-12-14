#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "eventHandlers.h"
#include "physicsHandlers.h"
#include "material.h"

#include <iostream>
#include <string>
#include <sstream>

// Size of "blocks" in pixels
#define PIXEL_SIZE 10
// Number of pixels
#define SCREEN_SIZE 100
// Throttles how fast things happen
#define TICK_RESET 256

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(PIXEL_SIZE * SCREEN_SIZE, PIXEL_SIZE * SCREEN_SIZE),
        "Sandbox Test");

    // Dynamic allocation of a 2D array (matrix)
    Cell **data = new Cell *[SCREEN_SIZE];
    for (int i = 0; i < SCREEN_SIZE; ++i)
    {
        data[i] = new Cell[SCREEN_SIZE];
    }

    Material material = BRICK;

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
            {
                // Deallocate memory for the data matrix
                for (int i = 0; i < SCREEN_SIZE; ++i)
                {
                    delete[] data[i];
                }
                delete[] data;
                window.close();
            }

            handleEvents(event, &material, data, SCREEN_SIZE);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tick == 0)
        {
            // Get the position where the mouse was clicked
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Calculate which cell we are in
            int row = ((int)mousePosition.y) / PIXEL_SIZE;
            int col = ((int)mousePosition.x) / PIXEL_SIZE;

            if (row < 0 or row >= SCREEN_SIZE or col < 0 or col >= SCREEN_SIZE)
                continue;

            data[row][col].material = material;

            if (material == WATER)
                data[row][col].fluid_level = 9;
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
                    if (data[i][j].material == BRICK)
                    {
                        sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                        shape.setFillColor(sf::Color(77, 26, 30));
                        shape.setPosition(sf::Vector2f(PIXEL_SIZE * j, PIXEL_SIZE * i));
                        window.draw(shape);
                    }
                    else if (data[i][j].material == SAND)
                    {
                        sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                        shape.setFillColor(sf::Color(232, 181, 114));
                        shape.setPosition(sf::Vector2f(PIXEL_SIZE * j, PIXEL_SIZE * i));
                        window.draw(shape);
                    }
                    else if (data[i][j].material == WATER)
                    {
                        // Fluid height function be Fh(x) where x is a fluid level [0, 9]
                        // Fh(9) = 1, Fh(0) = 0, Fh(x) = (1/9)x
                        double fluidHeightScaler = (1 / 9) * data[i][j].fluid_level;
                        sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                        shape.setFillColor(sf::Color(30, 192, 232));
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
