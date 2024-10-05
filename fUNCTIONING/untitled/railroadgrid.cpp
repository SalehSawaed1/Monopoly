#include "railroadgrid.h"

// Constructor
RailroadGrid::RailroadGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight,
                           const std::string& name, float price)
    : Grid(topLeft, topRight, bottomLeft, bottomRight), m_name(name), m_price(price) {}

// Override of getName() to return the name of the railroad
std::string RailroadGrid::getName() const {
    return m_name;
}

// Get price of the railroad
float RailroadGrid::getPrice() const {
    return m_price;
}
