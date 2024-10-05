#include "surprisegrid.h"
#include <cstdlib>  // For random generation
#include <ctime>    // For seeding randomness

// Constructor
SurpriseGrid::SurpriseGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name)
        : SpecialGrid(topLeft, topRight, bottomLeft, bottomRight, name) {
    // Initialize some surprise messages
    surprises = {
            "Get out of Jail Free card",
            "Pay poor tax of $15",
            "Collect $50",
            "Go to Go and collect $200",
            "Go directly to Jail"
    };

    // Seed the random number generator with the current time
    std::srand(std::time(nullptr));
}

// Return a random surprise from the list
std::string SurpriseGrid::getSurprise() const {
    int randomIndex = std::rand() % surprises.size();  // Random index between 0 and the size of surprises
    return surprises[randomIndex];
}
