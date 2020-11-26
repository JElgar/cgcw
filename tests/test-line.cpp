#include <gtest/gtest.h>
#include <CanvasLine.h>
#include <math.h>

TEST(LineTest, TestLineConstructor) {
  CanvasPoint point1 = CanvasPoint(1, 2);
  CanvasPoint point2 = CanvasPoint(3, 4);
  CanvasLine line = CanvasLine(point1, point2);

  ASSERT_EQ(line.v0().x(), 1);
  ASSERT_EQ(line.v0().y(), 2);
  ASSERT_EQ(line.v1().x(), 3);
  ASSERT_EQ(line.v1().y(), 4);
}


TEST(LineTest, TestLineLength) {
  CanvasPoint point1 = CanvasPoint(1, 1);
  CanvasPoint point2 = CanvasPoint(1, 5);
  CanvasLine line = CanvasLine(point1, point2);

  ASSERT_EQ(line.length(), 4);
  
  point2 = CanvasPoint(5, 5);
  line = CanvasLine(point1, point2);

  ASSERT_EQ((float)line.length(), (float)sqrt(32));
}


TEST(LineTest, FindIntersectionWithY) {
  CanvasPoint point1 = CanvasPoint(1, 1);
  CanvasPoint point2 = CanvasPoint(3, 3);
  CanvasLine line = CanvasLine(point1, point2);

  CanvasPoint intersection = line.findIntersectionWithY(2);
  ASSERT_EQ(intersection.x(), 2);
  ASSERT_EQ(intersection.y(), 2);
}


TEST(LineTest, FindIntersectionWithYException) {
  CanvasPoint point1 = CanvasPoint(1, 1);
  CanvasPoint point2 = CanvasPoint(3, 3);
  CanvasLine line = CanvasLine(point1, point2);

  CanvasPoint intersection = line.findIntersectionWithY(2);
  ASSERT_EQ(intersection.x(), 2);
  ASSERT_EQ(intersection.y(), 2);
}
