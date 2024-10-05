#include "freeparkinggrid.h"

FreeParkingGrid::FreeParkingGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name)
    : SpecialGrid(topLeft, topRight, bottomLeft, bottomRight, name) { }
