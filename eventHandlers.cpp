#include "eventHandlers.h"
#include "material.h"
#include <iostream>

void handleEvents(sf::Event event, Material *material)
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
        default:
            break;
        }
    }
}