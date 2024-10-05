#ifndef POINTF_H
#define POINTF_H

struct PointF {
    double x, y;
    PointF(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

#endif // POINTF_H

