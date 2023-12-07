#include "physicsHandlers.h"
#include "material.h"

void updateData(Material **data, int screenSize)
{
    // We iterate through the rows bottom up, stopping at the second row
    for (int i = screenSize - 1; i > 0; i--)
    {
        // Iterate through the columns left to right
        for (int j = 0; j < screenSize; j++)
        {
            // If the cell we are looking at is air
            if (data[i][j] == AIR)
            {
                // And if the cell above us is a brick
                if (data[i - 1][j] == BRICK)
                {
                    // Let the brick "fall", i.e. swap the air and brick
                    data[i][j] = BRICK;
                    data[i - 1][j] = AIR;
                }

                // Handle Sand
                else if (data[i - 1][j] == SAND)
                {
                    data[i][j] = SAND;
                    data[i - 1][j] = AIR;
                }
                else if (j > 0 &&
                         data[i - 1][j - 1] == SAND &&
                         data[i][j - 1] != AIR)
                {
                    data[i][j] = SAND;
                    data[i - 1][j - 1] = AIR;
                }
                else if (j < screenSize - 1 &&
                         data[i - 1][j + 1] == SAND &&
                         data[i][j + 1] != AIR)
                {
                    data[i][j] = SAND;
                    data[i - 1][j + 1] = AIR;
                }
            }
        }
    }
}