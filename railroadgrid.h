#ifndef RAILROADGRID_H
#define RAILROADGRID_H

#include "Grid.h"
#include <string>

class RailroadGrid : public Grid {
public:
    // Constructor that takes the grid corners, name, and price
    RailroadGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight,
                 const std::string& name, float price);

    // Getter for the railroad name
    std::string getName() const override;

    // Getter for the price of the railroad
    float getPrice() const;
    float getRent(int numRailroadsOwned) const;

private:
    std::string m_name;  // Railroad name
    float m_price;       // Price of the railroad
};

#endif // RAILROADGRID_H
