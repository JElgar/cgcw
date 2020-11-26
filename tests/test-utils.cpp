#include <gtest/gtest.h>
#include <Utils.h>

TEST(UtilsTest, TestInterpolateSingleFloats) {
  std::vector<float> inters = interpolateSingleFloats(1, 10, 10);
  std::vector<float> exp_inters = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(inters.size(), 10);
  ASSERT_EQ(inters, exp_inters);
}
