#include <gtest/gtest.h>
#include <CanvasTriangle.h>
#include <Utils.h>


TEST(CanvasTriangleTest, TestDrawTriangle) {
  DrawingWindow window = DrawingWindow(512, 512, false);
    
  Colour colour = Colour(255, 0, 0);
  CanvasTriangle(CanvasPoint(0,0, -1), CanvasPoint(300,100, -1), CanvasPoint(100, 50, -1)).draw(colour, window);

  std::vector<uint32_t> exptectedPixelBuffer = readVectorFromFile("tests/fixtures/draw_triangle-512x512.txt");

  ASSERT_EQ(exptectedPixelBuffer, window.getPixelBuffer());
}

TEST(CanvasTriangleTest, TestFillTriangle) {
  DrawingWindow window = DrawingWindow(512, 512, false);
    
  Colour colour = Colour(0, 255, 255);
  CanvasTriangle(CanvasPoint(0,0, -1), CanvasPoint(255,400, -1), CanvasPoint(200, 200, -1)).fill(colour, window);

  std::vector<uint32_t> exptectedPixelBuffer = readVectorFromFile("tests/fixtures/fill_triangle-512x512.txt");

  ASSERT_EQ(exptectedPixelBuffer, window.getPixelBuffer());
}

TEST(CanvasTriangleTest, TestTextureMap) {
  DrawingWindow window = DrawingWindow(512, 512, false);
  TextureMap texture = TextureMap("assets/texture.ppm");

  TexturePoint texture1 = TexturePoint(170, 50);
  TexturePoint texture2 = TexturePoint(300, 300);
  TexturePoint texture3 = TexturePoint(50, 200);
    
  CanvasTriangle(CanvasPoint(160,10, -1, texture1), CanvasPoint(300,230, -1, texture2), CanvasPoint(10, 150, -1, texture3)).mapTexture(texture, window);

  std::vector<uint32_t> exptectedPixelBuffer = readVectorFromFile("tests/fixtures/textured_triangle-512x512.txt");

  ASSERT_EQ(exptectedPixelBuffer, window.getPixelBuffer());
}
