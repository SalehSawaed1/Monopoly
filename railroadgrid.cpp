#include "railroadgrid.h"
#include <iostream>

RailroadGrid::RailroadGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name, float price)
    : Grid(topLeft, topRight, bottomLeft, bottomRight), m_name(name), m_price(price) {}

std::string RailroadGrid::getName() const {
    return m_name;
}

float RailroadGrid::getPrice() const {
    return m_price;
}

float RailroadGrid::getRent(int numRailroadsOwned) const {
    switch (numRailroadsOwned) {
    case 1: return 50;
    case 2: return 100;
    case 3: return 150;
    case 4: return 200;
    default: return 0;
    }
}
