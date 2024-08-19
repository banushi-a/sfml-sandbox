#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "eventHandlers.hpp"
#include "physicsHandlers.hpp"
#include "material.hpp"
#include "RandomManager.hpp"

#include <iostream>
#include <string>
#include <sstream>

// Size of "blocks" in pixels
#define PIXEL_SIZE 5
// Number of pixels
#define SCREEN_SIZE 200

bool inBounds(int r, int c)
{
    return r >= 0 && c >= 0 && r < SCREEN_SIZE - 1 && c < SCREEN_SIZE - 1;
}

int main()
{
    // Make the window
    sf::RenderWindow window(
        sf::VideoMode(PIXEL_SIZE * SCREEN_SIZE, PIXEL_SIZE * SCREEN_SIZE),
        "Sandbox");

    window.setFramerateLimit(60);

    // Dynamic allocation of a 2D array (matrix)
    Cell **data = new Cell *[SCREEN_SIZE];
    for (int i = 0; i < SCREEN_SIZE; ++i)
    {
        data[i] = new Cell[SCREEN_SIZE];
    }

    Material material = BRICK;
    int spawnSize = 3;

    // Create a clock for measuring time elapsed
    sf::Clock clock;
    int tick = 0;

    // Main Loop of The Program
    while (window.isOpen())
    {
        // Calculate delta time
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
        tick += 1;

        // Calculate the FPS
        float fps = static_cast<int>((1.0f / dt) + 0.5f);

        // Set the window title with the current FPS
        std::ostringstream title;
        title << "Sandbox - FPS: " << fps;
        window.setTitle(title.str());

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
                window.setFramerateLimit(0);
                window.close();
            }

            handleEvents(event, &material, &spawnSize, data, SCREEN_SIZE);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
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
                    if (inBounds(i, j) && data[i][j].material == AIR && RandomManager::Instance().GetRandom() > 0.7)
                    {
                        data[i][j].material = material;
                        if (material == WATER || material == GASOLINE || material == FIRE)
                            data[i][j].fluid_level = 9;
                        data[i][j].last_updated = tick;
                    }
                }
            }
        }

        // Make the bricks "fall"
        updateData(data, SCREEN_SIZE, tick);

        // Clear the window and draw everything over
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
                    sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                    shape.setFillColor(sf::Color(30, 192, 232));
                    shape.setPosition(sf::Vector2f(PIXEL_SIZE * j, PIXEL_SIZE * i));

                    window.draw(shape);
                }
                else if (data[i][j].material == GASOLINE)
                {
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
                else if (data[i][j].material == STEAM)
                {
                    sf::RectangleShape shape(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                    shape.setFillColor(sf::Color(224, 224, 224));
                    shape.setPosition(sf::Vector2f(PIXEL_SIZE * j, PIXEL_SIZE * i));

                    window.draw(shape);
                }
            }
        }

        window.display();
    }
    return 0;
}