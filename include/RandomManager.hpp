#pragma once

#include <random>

class RandomManager
{
public:
    // Singleton pattern for having one single RandomManager
    // class at any given time
    static RandomManager &Instance();
    // Get a random number between 0 and 1
    float GetRandom();

    // Destructor
    ~RandomManager();

private:
    RandomManager();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
};