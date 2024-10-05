#include "utilitygrid.h"
#include <string>

// Constructor
UtilityGrid::UtilityGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight,
                         const std::string& name, int price)
    : Grid(topLeft, topRight, bottomLeft, bottomRight), m_name(name), m_price(price) {}

// Override of getName() to return the name of the utility
std::string UtilityGrid::getName() const {
    return m_name;
}

// Get price of the utility
int UtilityGrid::getPrice() const {
    return m_price;
}
