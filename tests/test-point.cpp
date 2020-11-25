#include <gtest/gtest.h>
#include <CanvasPoint.h>
#include <DrawingWindow.h>

TEST(PointTest, TestPointIsOnScreen) {
  DrawingWindow window = DrawingWindow(40, 40, false);

  CanvasPoint point1 = CanvasPoint(0, 2);
  ASSERT_EQ(point1.isOffScreen(window), false);

  point1 = CanvasPoint(-10, 2);
  ASSERT_EQ(point1.isOffScreen(window), true);

  point1 = CanvasPoint(0, 41);
  ASSERT_EQ(point1.isOffScreen(window), true);

  point1 = CanvasPoint(40, 0);
  ASSERT_EQ(point1.isOffScreen(window), true);
}

