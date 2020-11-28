#include <gtest/gtest.h>
#include <Utils.h>

TEST(UtilsTest, TestInterpolateSingleFloats) {
  std::vector<float> inters = interpolate<float>(1, 10, 10);
  std::vector<float> exp_inters = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(inters.size(), 10);
  ASSERT_EQ(inters, exp_inters);
}

TEST(UtilsTest, TestInRange) {
  float bound1  = 1.2;
  float bound2  = 2.2;
  float value = 1.5;

  ASSERT_EQ(inRange(value, bound1, bound2), true);
}

TEST(UtilsTest, TestInRangeSameValue) {
  float bound1  = 1.2;
  float bound2  = 2.2;
  float value = 1.2;

  ASSERT_EQ(inRange(value, bound1, bound2), true);
}


TEST(UtilsTest, TestInterpolateVec2) {
    
  glm::vec2 from = glm::vec2(195, 5);
  glm::vec2 to = glm::vec2(65, 330);
  std::vector<glm::vec2> interpolatedStuff = interpolate<glm::vec2>(from, to, 140);

  ASSERT_EQ(interpolatedStuff.size(), 140);
  ASSERT_EQ(interpolatedStuff[0], from);
  ASSERT_EQ(interpolatedStuff[139], to);
  //ASSERT_EQ((int)interpolatedStuff[69].x, (int)130);
  //ASSERT_EQ((int)interpolatedStuff[69].y, (int)167.5);
}
