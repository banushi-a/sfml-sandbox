#include "physicsHandlers.h"

void updateData(int **data, int screenSize)
{
    for (int i = screenSize; i > 0; --i)
    {
        for (int j = 0; j < screenSize; ++j)
        {
            if (data[i][j] == 0 and data[i - 1][j] == 1)
            {
                data[i][j] = 1;
                data[i - 1][j] = 0;
            }
        }
    }
}