#include <gtest/gtest.h>
#include <Utils.h>

TEST(UtilsTest, TestInterpolateSingleFloats) {
  std::vector<float> inters = interpolateSingleFloats(1, 10, 10);
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
