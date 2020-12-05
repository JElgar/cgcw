#include <gtest/gtest.h>
#include <Ray.h>
#include <ObjModel.h>

TEST(RayTest, TestCentralRayIntersectsBlueBox) {
  
  int windowSize = 512;

  DrawingWindow window = DrawingWindow(windowSize, windowSize, false);
  Camera camera = Camera(0, 0, 2, 400);
  ObjModel model = ObjModel("assets/", "textured-cornell-box.obj", 0.17);

  CanvasPoint point = CanvasPoint(windowSize/2, windowSize/2);
  Ray ray = Ray(point, camera, window);

  RayTriangleIntersection intersection = model.getClosestIntersection(ray);

  ASSERT_EQ(intersection.getIntersectedTriangle().material().getColour().pack(), Colour(0, 0, 255).pack());
}
