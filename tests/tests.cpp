#include "gtest/gtest.h"

// Include tests
#include "test-line.cpp"
#include "test-point.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
