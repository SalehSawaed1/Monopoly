#ifndef FREEPARKINGGRID_H
#define FREEPARKINGGRID_H

#include "specialgrid.h"
#include "Grid.h"

class FreeParkingGrid : public SpecialGrid {
public:
    FreeParkingGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name);
};

#endif // FREEPARKINGGRID_H
