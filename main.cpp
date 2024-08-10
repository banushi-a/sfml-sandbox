#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "eventHandlers.h"
#include "physicsHandlers.h"
#include "material.h"

#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <chrono>

// Size of "blocks" in pixels
#define PIXEL_SIZE 5
// Number of pixels
#define SCREEN_SIZE 200
// Throttles how fast things happen
#define TICK_RESET 256

bool inBounds(int r, int c)
{
    return r >= 0 && c >= 0 && r < SCREEN_SIZE - 1 && c < SCREEN_SIZE - 1;
}

int main()
{
    // Use the current time as a seed for the random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // Define the distribution for floating-point numbers between 0 and 1
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // Make the window
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
    int spawnSize = 3;

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

            handleEvents(event, &material, &spawnSize, data, SCREEN_SIZE);
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

            // Spawn the material randomly in a surrounding area
            for (int i = row - spawnSize + 2; i <= row + (spawnSize - 2); ++i)
            {
                for (int j = col - spawnSize + 2; j <= col + (spawnSize - 2); ++j)
                {
                    if (inBounds(i, j) && data[i][j].material == AIR && distribution(generator) > 0.7)
                    {
                        data[i][j].material = material;
                        if (material == WATER || material == GAS || material == FIRE)
                            data[i][j].fluid_level = 9;
                    }
                }
            }
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
                    else if (data[i][j].material == GAS)
                    {
                        // Fluid height function be Fh(x) where x is a fluid level [0, 9]
                        // Fh(9) = 1, Fh(0) = 0, Fh(x) = (1/9)x
                        double fluidHeightScaler = (1 / 9) * data[i][j].fluid_level;
                        sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                        shape.setFillColor(sf::Color(89, 89, 89));
                        shape.setPosition(sf::Vector2f(PIXEL_SIZE * j, PIXEL_SIZE * i));

                        window.draw(shape);
                    }
                    else if (data[i][j].material == FIRE)
                    {
                        sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                        shape.setFillColor(sf::Color(163, 33, 33));
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