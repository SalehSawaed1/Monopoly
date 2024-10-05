#ifndef JAILGRID_H
#define JAILGRID_H

#include "specialgrid.h"

class JailGrid : public SpecialGrid {
public:
    JailGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name);
};

#endif // JAILGRID_H
