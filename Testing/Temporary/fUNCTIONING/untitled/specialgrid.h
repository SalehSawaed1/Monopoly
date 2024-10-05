#ifndef SPECIALGRID_H
#define SPECIALGRID_H

#include "Grid.h"
#include <string>

class SpecialGrid : public Grid {
public:
    SpecialGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name);

    std::string getName() const override;

private:
    std::string m_name;
};

#endif // SPECIALGRID_H
