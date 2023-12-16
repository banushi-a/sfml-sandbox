#include "physicsHandlers.h"
#include "material.h"
#include <cmath>

void handleWaterCell(Cell **data, int screenSize, int i, int j)
{

    // If there is a row below us and if there is air below the water
    if (i < screenSize - 1 && data[i + 1][j].material == AIR)
    {
        // Drop the water
        data[i + 1][j].material = WATER;
        data[i + 1][j].fluid_level = 9;

        data[i][j].material = AIR;
        data[i][j].fluid_level = 0;
    }
    // If there is a row to the right of us and it is air
    else if (j < screenSize - 1 && data[i][j + 1].material == AIR)
    {
        // Move the water right
        data[i][j + 1].material = WATER;
        data[i][j + 1].fluid_level = (int)(data[i][j].fluid_level / 2);
        data[i][j].material = AIR;
        data[i][j].fluid_level = (int)std::ceil(data[i][j].fluid_level / 2);
    }
    // If there is a row to the left of us
    else if (j > 0 && data[i][j - 1].material == AIR)
    {
        // Move the water left
        data[i][j - 1].material = WATER;
        data[i][j - 1].fluid_level = (int)(data[i][j].fluid_level / 2);
        data[i][j].material = AIR;
        data[i][j].fluid_level = (int)std::ceil(data[i][j].fluid_level / 2);
    }
}

void handleBrickCell(Cell **data, int screenSize, int i, int j)
{
    // If their is air or water below us
    if (i < screenSize - 1 && (data[i + 1][j].material == AIR || data[i + 1][j].material == WATER))
    {
        // Let the brick "fall", i.e. swap the air and brick
        data[i][j].material = data[i + 1][j].material;
        data[i + 1][j].material = BRICK;
    }
}

void handleSandCell(Cell **data, int screenSize, int i, int j)
{
    // If there is a row below us
    if (i < screenSize - 1)
    {
        // If the sand is above air
        if (data[i + 1][j].material == AIR)
        {
            data[i][j].material = AIR;
            data[i + 1][j].material = SAND;
        }
        // If there is air to the right and down of us
        else if (j < screenSize - 1 &&
                 data[i + 1][j + 1].material == AIR &&
                 data[i + 1][j].material != AIR)
        {
            data[i + 1][j + 1].material = SAND;
            data[i][j].material = AIR;
        }
        // If there is air to the left and down of us
        else if (j > 0 &&
                 data[i + 1][j - 1].material == AIR &&
                 data[i + 1][j].material != AIR)
        {
            data[i + 1][j - 1].material = SAND;
            data[i][j].material = AIR;
        }
    }
}

void updateData(Cell **data, int screenSize)
{
    // We iterate through the rows bottom up, stopping at the second row
    for (int i = screenSize - 1; i >= 0; i--)
    {
        // Iterate through the columns left to right
        for (int j = 0; j < screenSize; j++)
        {
            // If the cell we are looking at is water
            if (data[i][j].material == WATER)
            {
                handleWaterCell(data, screenSize, i, j);
            }
            else if (data[i][j].material == BRICK)
            {
                handleBrickCell(data, screenSize, i, j);
            }
            else if (data[i][j].material == SAND)
            {
                handleSandCell(data, screenSize, i, j);
            }
        }
    }
}