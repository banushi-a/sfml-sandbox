#ifndef MATERIAL_ENUM
#define MATERIAL_ENUM

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
    // ----- Member variables --------------//
    // Material of the cell
    Material material;
    // Fluid level of the cell is an integer in [0, 9]
    int fluid_level;
    // Last tick that the cell was updated
    int last_updated;

    // ----- Constructors --------------//
    Cell() : material(AIR), fluid_level(0), last_updated(0) {}
    Cell(Material m, int fL, int lU) : material(m), fluid_level(fL), last_updated(lU) {}
};

#endif