#include <gtest/gtest.h>
#include <ObjModel.h>
#include <Utils.h>

TEST(ModelTest, TestDrawTriangle) {

  std::cout << "Running test" << std::endl;
  // Setup
  DrawingWindow window = DrawingWindow(512, 512, false);
  Camera camera = Camera(0, 0, 2, 15);
  ObjModel model = ObjModel("assets/", "textured-cornell-box.obj", 0.17);
  model.draw(window, camera, 40);

  std::vector<uint32_t> exptectedPixelBuffer = readVectorFromFile("tests/fixtures/draw_model_with_texture-512x512.txt");

  ASSERT_EQ(exptectedPixelBuffer, window.getPixelBuffer());
}
