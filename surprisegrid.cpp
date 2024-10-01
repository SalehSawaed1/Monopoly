#include "surprisegrid.h"
#include <cstdlib>  // For random generation
#include <ctime>    // For seeding randomness

// Constructor
SurpriseGrid::SurpriseGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name)
    : SpecialGrid(topLeft, topRight, bottomLeft, bottomRight, name) {
    // Initialize some surprise messages
    surprises = {
        "Advance to Go (Collect $200)",
        "Bank pays you dividend of $50",
        "Go back 3 spaces",
        "Go directly to Jail – do not pass Go, do not collect $200",
        "Make general repairs on all your property – For each house pay $25 – For each hotel $100",
        "Pay poor tax of $15",
        "Take a trip to Reading Railroad – If you pass Go collect $200",
        "Take a walk on the Boardwalk – Advance token to Boardwalk",
        "You have been elected Chairman of the Board – Pay each player $50",
        "Your building loan matures – Collect $150",
        "Get out of Jail Free – This card may be kept until needed or traded",
        "Advance to Illinois Ave. – If you pass Go, collect $200",
        "Advance to St. Charles Place – If you pass Go, collect $200",
        "You are assessed for street repairs – $40 per house, $115 per hotel",
        "Advance to nearest Utility – If unowned you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown.",
        "Advance to nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental."
    };

    // Seed the random number generator with the current time
    std::srand(std::time(nullptr));
}

// Return a random surprise from the list
std::string SurpriseGrid::getSurprise() const {
    int randomIndex = std::rand() % surprises.size();  // Random index between 0 and the size of surprises
    return surprises[randomIndex];
}
