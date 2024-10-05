#ifndef GOTOJAILGRID_H
#define GOTOJAILGRID_H

#include "specialgrid.h"
#include "PointF.h"  // Assuming PointF is your custom structure
#include <string>    // For std::string

class GoToJailGrid : public SpecialGrid {
public:
    // Constructor that takes the grid corners and the name as std::string
    GoToJailGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name);
};

#endif // GOTOJAILGRID_H
