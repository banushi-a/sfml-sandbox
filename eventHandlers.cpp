#include "eventHandlers.h"
#include "material.h"
#include <iostream>

void handleEvents(sf::Event event, Material *material)
{
    if (event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::S)
    {
        *material = SAND;
    }
    else if (event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::B)
    {
        *material = BRICK;
    }
}