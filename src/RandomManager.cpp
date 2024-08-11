#include "RandomManager.hpp"
#include <random>
#include <chrono>

RandomManager::RandomManager()
{
    // Use the current time as a seed for the random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    RandomManager::generator = gen;
    // Define the distribution for floating-point numbers between 0 and 1
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    RandomManager::distribution = dist;
}

RandomManager &RandomManager::Instance()
{
    static RandomManager *instance = new RandomManager();
    return *instance;
}

float RandomManager::GetRandom()
{
    return RandomManager::distribution(RandomManager::generator);
}