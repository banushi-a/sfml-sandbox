#ifndef EVENT_HANDLERS
#define EVENT_HANDLERS

#include <SFML/Graphics.hpp>
#include "material.h"

void handleEvents(sf::Event event, Material *material, Cell **data, int SCREEN_SIZE);

#endif
