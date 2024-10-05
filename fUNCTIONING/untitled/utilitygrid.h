#ifndef UTILITYGRID_H
#define UTILITYGRID_H

#include "Grid.h"
#include <string>

class UtilityGrid : public Grid {
public:
    // Constructor that takes the grid corners, name, and price
    UtilityGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight,
                const std::string& name, int price);

    // Getter for the utility name
    std::string getName() const override;

    // Getter for the price of the utility
    int getPrice() const;

    // Implementation of the landing behavior

private:
    std::string m_name; // Utility name (e.g., "Electric Company", "Water Works")
    int m_price;    // Price of the utility
};

#endif // UTILITYGRID_H
