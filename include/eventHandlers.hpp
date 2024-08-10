#ifndef EVENT_HANDLERS
#define EVENT_HANDLERS

#include <SFML/Graphics.hpp>
#include "material.hpp"

void handleEvents(sf::Event event, Material *material, int *spawnSize, Cell **data, int SCREEN_SIZE);

#endif
