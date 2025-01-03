#ifndef MATERIAL_ENUM
#define MATERIAL_ENUM

#include <SFML/Graphics.hpp>

#include "RandomManager.hpp"

// Type of Material Available in Sandbox
enum Material
{
    AIR,      // 0
    BRICK,    // 1
    SAND,     // 2
    WATER,    // 3
    GASOLINE, // 4
    FIRE,     // 5
    STEAM,    //  6
};

// Define the type a cell can be
struct Cell
{
    // ----- Member variables -------------- //
    // Material of the cell
    Material material;
    // Color of the cell
    sf::Color color;
    // Fluid level of the cell is an integer in [0, 9]
    int fluid_level;
    // Last tick that the cell was updated
    int last_updated;

    // ----- Constructors -------------- //
    Cell() : material(AIR), fluid_level(0), last_updated(0), color(sf::Color(0, 0, 0)) {}
    Cell(Material m, int fL, int lU) : material(m), fluid_level(fL), last_updated(lU), color(GetColorForMaterial(m)) {}

    // ----- Methods -------------- //
    static sf::Color GetColorForMaterial(Material m)
    {
        switch (m)
        {
        case WATER:
            if (RandomManager::Instance().GetRandom() < 0.5)
                return sf::Color(30, 192, 255);
            return sf::Color(30, 192, 232);
        case GASOLINE:
            if (RandomManager::Instance().GetRandom() < 0.5)
                return sf::Color(100, 100, 100);
            return sf::Color(89, 89, 89);
        case BRICK:
            return sf::Color(77, 26, 30);
        case SAND:
            if (RandomManager::Instance().GetRandom() < 0.5)
                return sf::Color(232, 181, 114);
            return sf::Color(210, 134, 34);
        case FIRE:
            if (RandomManager::Instance().GetRandom() < 0.5)
                return sf::Color(163, 33, 33);
            return sf::Color(138, 18, 18);
        case STEAM:
            return sf::Color(224, 224, 224);
        case AIR:
        default:
            return sf::Color(0, 0, 0);
        }
    }

    // TODO: Use these in physicsHandlers
    void SetMaterial(Material m, int currTick)
    {
        material = m;                   // Set the material
        color = GetColorForMaterial(m); // Set the corresponding color
        last_updated = currTick;
    }

    void SetMaterial(Material m, sf::Color c, int currTick)
    {
        material = m;
        color = c;
        last_updated = currTick;
    }
};

#endif