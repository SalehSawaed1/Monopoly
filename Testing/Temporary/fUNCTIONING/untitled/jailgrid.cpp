#include "jailgrid.h"

// Constructor for JailGrid
JailGrid::JailGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name)
    : SpecialGrid(topLeft, topRight, bottomLeft, bottomRight, name) {
    // The name could be "Jail" or "Just Visiting" based on the location on the board
}
