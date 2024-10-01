#ifndef GRID_H
#define GRID_H
#include "PointF.h"
#include <string>



class Grid {
public:
    Grid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight);

    PointF getTopLeft() const;
    PointF getTopRight() const;
    PointF getBottomLeft() const;
    PointF getBottomRight() const;
    virtual ~Grid() {}

    // Function to calculate a random point inside the grid
    PointF calculateRandomPoint() const;

    // Virtual function for grid name, to be overridden by derived classes
    virtual std::string getName() const = 0;

protected:
    PointF m_topLeft;
    PointF m_topRight;
    PointF m_bottomLeft;
    PointF m_bottomRight;
};

#endif // GRID_H
