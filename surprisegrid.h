#ifndef SURPRISEGRID_H
#define SURPRISEGRID_H

#include "specialgrid.h"
#include <vector>
#include <string>

class SurpriseGrid : public SpecialGrid {
public:
    SurpriseGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name);

    // Returns a random surprise from the list
    std::string getSurprise() const;

private:
    std::vector<std::string> surprises;
};

#endif // SURPRISEGRID_H
