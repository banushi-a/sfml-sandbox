#include "eventHandlers.h"
#include "material.h"
#include <iostream>

void handleEvents(sf::Event event, Material *material, Cell **data, int SCREEN_SIZE)
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
            *material = GAS;
            break;
        case sf::Keyboard::F:
            *material = FIRE;
            break;
        case sf::Keyboard::R:
            for (int i = 0; i < SCREEN_SIZE; ++i)
            {
                delete[] data[i];
                data[i] = new Cell[SCREEN_SIZE];
            }
            break;
        default:
            break;
        }
    }
}