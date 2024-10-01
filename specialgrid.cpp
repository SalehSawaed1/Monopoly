#include "specialgrid.h"
#include <string>

// Constructor
SpecialGrid::SpecialGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name)
    : Grid(topLeft, topRight, bottomLeft, bottomRight), m_name(name) { }

// Override of getName() to return the name of the special grid
std::string SpecialGrid::getName() const {
    return m_name;
}
