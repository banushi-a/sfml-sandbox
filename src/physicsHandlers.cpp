#include <iostream>

#include "physicsHandlers.hpp"
#include "material.hpp"
#include "RandomManager.hpp"

#include <cmath>

bool isFluid(Material material)
{
    return material == WATER || material == GASOLINE;
}

void handleFluid(Cell **data, int screenSize, int i, int j, Material fluid, int currTick)
{
    // If there is a row below us and if there is air below the fluid
    if (i < screenSize - 1 && data[i + 1][j].material == AIR)
    {
        // Drop the water
        data[i + 1][j].material = fluid;
        data[i + 1][j].fluid_level = 9;
        data[i + 1][j].last_updated = currTick;

        data[i][j].material = AIR;
        data[i][j].fluid_level = 0;
        data[i][j].last_updated = currTick;
    }
    // If there is a row to the right of us and it is air
    else if (j < screenSize - 1 && data[i][j + 1].material == AIR)
    {
        // Move the fluid right
        data[i][j + 1].material = fluid;
        data[i][j + 1].fluid_level = (int)(data[i][j].fluid_level / 2);
        data[i][j + 1].last_updated = currTick;

        data[i][j].material = AIR;
        data[i][j].fluid_level = (int)std::ceil(data[i][j].fluid_level / 2);
        data[i][j].last_updated = currTick;
    }
    // If there is a row to the left of us
    else if (j > 0 && data[i][j - 1].material == AIR)
    {
        // Move the fluid left
        data[i][j - 1].material = fluid;
        data[i][j - 1].fluid_level = (int)(data[i][j].fluid_level / 2);
        data[i][j - 1].last_updated = currTick;

        data[i][j].material = AIR;
        data[i][j].fluid_level = (int)std::ceil(data[i][j].fluid_level / 2);
        data[i][j].last_updated = currTick;
    }
}

void handleWaterCell(Cell **data, int screenSize, int i, int j, int currTick)
{
    handleFluid(data, screenSize, i, j, WATER, currTick);
}

void handleGasolineCell(Cell **data, int screenSize, int i, int j, int currTick)
{
    handleFluid(data, screenSize, i, j, GASOLINE, currTick);
}

void handleBrickCell(Cell **data, int screenSize, int i, int j, int currTick)
{
    // If their is fluid below us
    if (i < screenSize - 1 && isFluid(data[i + 1][j].material))
    {
        // Let the brick "fall", i.e. swap the air and brick
        data[i][j].material = data[i + 1][j].material;
        data[i][j].fluid_level = data[i + 1][j].fluid_level;
        data[i][j].last_updated = currTick;

        data[i + 1][j].material = BRICK;
        data[i + 1][j].fluid_level = 0;
        data[i + 1][j].last_updated = currTick;
    }
    else if (i < screenSize - 1 && data[i + 1][j].material == AIR)
    {
        // Let the brick "fall", i.e. swap the air and brick
        data[i][j].material = AIR;
        data[i][j].last_updated = currTick;

        data[i + 1][j].material = BRICK;
        data[i + 1][j].last_updated = currTick;
    }
}

void handleSandCell(Cell **data, int screenSize, int i, int j)
{
    // If there is a row below us
    if (i < screenSize - 1)
    {
        // If the sand is above air
        if (data[i + 1][j].material == AIR || isFluid(data[i + 1][j].material))
        {
            data[i][j].material = data[i + 1][j].material;
            data[i + 1][j].material = SAND;
        }
        // If there is air to the right and down of us
        else if (j < screenSize - 1 &&
                 (data[i + 1][j + 1].material == AIR || isFluid(data[i + 1][j + 1].material)) &&
                 data[i + 1][j].material != AIR)
        {
            data[i][j].material = data[i + 1][j + 1].material;
            data[i + 1][j + 1].material = SAND;
        }
        // If there is air to the left and down of us
        else if (j > 0 &&
                 (data[i + 1][j - 1].material == AIR || isFluid(data[i + 1][j - 1].material)) &&
                 data[i + 1][j].material != AIR)
        {
            data[i][j].material = data[i + 1][j - 1].material;
            data[i + 1][j - 1].material = SAND;
        }
    }
}

void handleFireCell(Cell **data, int screenSize, int i, int j)
{
    // Remove "energy" from the current fire cell
    if (data[i][j].fluid_level == 0)
    {
        data[i][j].material = AIR;
    }
    else
    {
        --data[i][j].fluid_level;
    }

    // If there is a row below us
    if (i < screenSize - 1)
    {
        if (data[i + 1][j].material == GASOLINE && RandomManager::Instance().GetRandom() > 0.5)
        {
            data[i + 1][j].material = FIRE;
            data[i + 1][j].fluid_level = 9;
        }

        if (data[i + 1][j].material == WATER && RandomManager::Instance().GetRandom() > 0.5)
        {
            data[i + 1][j].material = STEAM;
        }
    }

    // If there is a row above us
    if (i > 0)
    {
        if (data[i - 1][j].material == GASOLINE && RandomManager::Instance().GetRandom() > 0.5)
        {
            data[i - 1][j].material = FIRE;
            data[i - 1][j].fluid_level = 9;
        }

        if (data[i - 1][j].material == WATER && RandomManager::Instance().GetRandom() > 0.5)
        {
            data[i - 1][j].material = STEAM;
        }
    }

    // If there is a column before us
    if (j > 0)
    {
        if (data[i][j - 1].material == GASOLINE && RandomManager::Instance().GetRandom() > 0.5)
        {
            data[i][j - 1].material = FIRE;
            data[i][j - 1].fluid_level = 9;
        }

        if (data[i][j - 1].material == WATER && RandomManager::Instance().GetRandom() > 0.5)
        {
            data[i][j - 1].material = STEAM;
        }
    }

    // If there is a column after us
    if (j < screenSize - 1)
    {
        if (data[i][j + 1].material == GASOLINE && RandomManager::Instance().GetRandom() > 0.5)
        {
            data[i][j + 1].material = FIRE;
            data[i][j + 1].fluid_level = 9;
        }

        if (data[i][j + 1].material == WATER && RandomManager::Instance().GetRandom() > 0.5)
        {
            data[i][j + 1].material = STEAM;
        }
    }
}

void handleSteamCell(Cell **data, int screenSize, int i, int j, int currTick)
{
    // If there is a row above us and if there is air above the steam
    if (i > 0 && data[i - 1][j].material == AIR)
    {
        // Let the steam float up
        data[i - 1][j].material = STEAM;
        data[i - 1][j].last_updated = currTick;

        data[i][j].material = AIR;
        data[i][j].last_updated = currTick;
    }
    // If there is a row to the right of us and it is air
    else if (j < screenSize - 1 && data[i][j + 1].material == AIR)
    {
        // Move the steam right
        data[i][j + 1].material = STEAM;
        data[i][j + 1].last_updated = currTick;

        data[i][j].material = AIR;
        data[i][j].last_updated = currTick;
    }
    // If there is a row to the left of us
    else if (j > 0 && data[i][j - 1].material == AIR)
    {
        // Move the steam left
        data[i][j - 1].material = STEAM;
        data[i][j - 1].last_updated = currTick;

        data[i][j].material = AIR;
        data[i][j].last_updated = currTick;
    }
}

void updateData(Cell **data, int screenSize, int currTick)
{
    // We iterate through the rows bottom up, stopping at the second row
    for (int i = screenSize - 1; i >= 0; i--)
    {
        // Iterate through the columns left to right
        for (int j = 0; j < screenSize; j++)
        {
            // Don't update the cell if we have already done so this tick
            if (data[i][j].last_updated == currTick)
                continue;

            switch (data[i][j].material)
            {
            case WATER:
                handleWaterCell(data, screenSize, i, j, currTick);
                break;
            case GASOLINE:
                handleGasolineCell(data, screenSize, i, j, currTick);
                break;
            case BRICK:
                handleBrickCell(data, screenSize, i, j, currTick);
                break;
            case SAND:
                handleSandCell(data, screenSize, i, j);
                break;
            case FIRE:
                handleFireCell(data, screenSize, i, j);
                break;
            case STEAM:
                handleSteamCell(data, screenSize, i, j, currTick);
                break;
            default:
                std::cout << "Unsupported Material, ID: " << data[i][j].material << std::endl;
                break;
            }
        }
    }
}