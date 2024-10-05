#include "Grid.h"
#include <random>

// Constructor to initialize the grid with four corner points
Grid::Grid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight)
    : m_topLeft(topLeft), m_topRight(topRight), m_bottomLeft(bottomLeft), m_bottomRight(bottomRight) {}

// Getters for the corner points of the grid
PointF Grid::getTopLeft() const {
    return m_topLeft;
}

PointF Grid::getTopRight() const {
    return m_topRight;
}

PointF Grid::getBottomLeft() const {
    return m_bottomLeft;
}

PointF Grid::getBottomRight() const {
    return m_bottomRight;
}

// Function to calculate a random point inside the grid
PointF Grid::calculateRandomPoint() const {
    double gridWidth = m_bottomRight.x - m_topLeft.x;
    double gridHeight = m_bottomRight.y - m_topLeft.y;

    // Use standard C++ random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.2, 0.8);  // Random number between 0.2 and 0.8

    double randomX = m_topLeft.x + dis(gen) * gridWidth;
    double randomY = m_topLeft.y + dis(gen) * gridHeight;

    return PointF(randomX, randomY);
}

// Default name for the grid
std::string Grid::getName() const {
    return "Unknown Grid";
}
