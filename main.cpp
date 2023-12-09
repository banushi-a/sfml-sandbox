#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "eventHandlers.h"
#include "physicsHandlers.h"
#include "material.h"
#include <iostream>

// Size of "blocks" in pixels
#define PIXEL_SIZE 10
// Number of pixels
#define SCREEN_SIZE 100
// Throttles how fast things happen
#define TICK_RESET 240

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(PIXEL_SIZE * SCREEN_SIZE, PIXEL_SIZE * SCREEN_SIZE),
        "Sandbox Test");

    // Dynamic allocation of a 2D array (matrix)
    Material **data = new Material *[SCREEN_SIZE];
    for (int i = 0; i < SCREEN_SIZE; ++i)
    {
        data[i] = new Material[SCREEN_SIZE];
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

            handleEvents(event, &material);
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

            data[row][col] = material;
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
                    if (data[i][j] == BRICK)
                    {
                        sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                        shape.setFillColor(sf::Color(77, 26, 30));
                        shape.setPosition(sf::Vector2f(PIXEL_SIZE * j, PIXEL_SIZE * i));
                        window.draw(shape);
                    }
                    else if (data[i][j] == SAND)
                    {
                        sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                        shape.setFillColor(sf::Color(232, 181, 114));
                        shape.setPosition(sf::Vector2f(PIXEL_SIZE * j, PIXEL_SIZE * i));
                        window.draw(shape);
                    }
                    else if (data[i][j] == WATER)
                    {
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
