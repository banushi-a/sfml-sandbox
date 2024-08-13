#include "eventHandlers.hpp"
#include "material.hpp"
#include <iostream>

void handleEvents(sf::Event event, Material *material, int *spawnSize, Cell **data, int SCREEN_SIZE)
{
    // If a key was presssed
    if (event.type == sf::Event::KeyReleased)
    {
        // Change the material accordingly
        switch (event.key.code)
        {
        case sf::Keyboard::S:
            *material = SAND;
            break;
        case sf::Keyboard::B:
            *material = BRICK;
            break;
        case sf::Keyboard::W:
            *material = WATER;
            break;
        case sf::Keyboard::G:
            *material = GASOLINE;
            break;
        case sf::Keyboard::F:
            *material = FIRE;
            break;
        case sf::Keyboard::T:
            *material = STEAM;
            break;
        case sf::Keyboard::R:
            for (int i = 0; i < SCREEN_SIZE; ++i)
            {
                delete[] data[i];
                data[i] = new Cell[SCREEN_SIZE];
            }
            break;
        case sf::Keyboard::Num1:
            *spawnSize = 2;
            break;
        case sf::Keyboard::Num3:
            *spawnSize = 3;
            break;
        case sf::Keyboard::Num5:
            *spawnSize = 5;
            break;
        case sf::Keyboard::Num7:
            *spawnSize = 7;
            break;
        case sf::Keyboard::Num9:
            *spawnSize = 9;
            break;
        default:
            break;
        }
    }
}