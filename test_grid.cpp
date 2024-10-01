#include <gtest/gtest.h>
#include "Grid.h"

// Example test case for the Grid class
TEST(GridTest, GetTopLeft) {
    QPointF topLeft(0, 0);
    QPointF topRight(1, 0);
    QPointF bottomLeft(0, 1);
    QPointF bottomRight(1, 1);

    Grid grid(topLeft, topRight, bottomLeft, bottomRight);

    EXPECT_EQ(grid.getTopLeft(), topLeft);
}

TEST(GridTest, CalculateRandomPoint) {
    QPointF topLeft(0, 0);
    QPointF topRight(1, 0);
    QPointF bottomLeft(0, 1);
    QPointF bottomRight(1, 1);

    Grid grid(topLeft, topRight, bottomLeft, bottomRight);

    QPointF randomPoint = grid.calculateRandomPoint();
    EXPECT_GE(randomPoint.x(), topLeft.x());
    EXPECT_LE(randomPoint.x(), topRight.x());
    EXPECT_GE(randomPoint.y(), topLeft.y());
    EXPECT_LE(randomPoint.y(), bottomLeft.y());
}
