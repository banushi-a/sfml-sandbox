#include "physicsHandlers.h"
#include "material.h"

void handleBricksAroundAir(Material **data, int screenSize, int i, int j)
{
    // If the brick is above us is
    if (i > 0 && data[i - 1][j] == BRICK)
    {
        // Let the brick "fall", i.e. swap the air and brick
        data[i][j] = BRICK;
        data[i - 1][j] = AIR;
    }
}

void handleSandAroundAir(Material **data, int screenSize, int i, int j)
{
    // If there is a row above us
    if (i > 0)
    {
        // If the sand is above air
        if (data[i - 1][j] == SAND)
        {
            data[i][j] = SAND;
            data[i - 1][j] = AIR;
        }
        // If the sand is up and to the left of us
        else if (j > 0 &&
                 data[i - 1][j - 1] == SAND &&
                 data[i][j - 1] != AIR)
        {
            data[i][j] = SAND;
            data[i - 1][j - 1] = AIR;
        }
        // If the sand is up and to the right of us
        else if (j < screenSize - 1 &&
                 data[i - 1][j + 1] == SAND &&
                 data[i][j + 1] != AIR)
        {
            data[i][j] = SAND;
            data[i - 1][j + 1] = AIR;
        }
    }
}

void handleWaterCell(Material **data, int screenSize, int i, int j)
{
    // If there is a row below us and if there is air below the water
    if (i < screenSize - 1 && data[i + 1][j] == AIR)
    {
        // Drop the water
        data[i + 1][j] = WATER;
        data[i][j] = AIR;
    }

    // If there is a row to the left of us and if there is air to the right of the water
    else if (j > 0 && data[i][j - 1] == AIR)
    {
        // Move the water right
        data[i][j - 1] = WATER;
        data[i][j] = AIR;
    }

    // If there is a row to the right of us and
    if (j < screenSize - 1 && data[i][j + 1] == AIR)
    {
        data[i][j + 1] = WATER;
        data[i][j] = AIR;
    }
}

void updateData(Material **data, int screenSize)
{
    // We iterate through the rows bottom up, stopping at the second row
    for (int i = screenSize - 1; i >= 0; i--)
    {
        // Iterate through the columns left to right
        for (int j = 0; j < screenSize; j++)
        {
            // If the cell we are looking at is air
            if (data[i][j] == AIR)
            {
                handleBricksAroundAir(data, screenSize, i, j);
                handleSandAroundAir(data, screenSize, i, j);
            }
            // If the cell we are looking at is water
            if (data[i][j] == WATER)
            {
                handleWaterCell(data, screenSize, i, j);
            }
        }
    }
}