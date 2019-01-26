#include "gtest/gtest.h"
#include "../src/test.cpp"

TEST(add, addFunction)
{
    EXPECT_EQ(25, add(20, 5));
    EXPECT_EQ(0, add(0, 0));
    EXPECT_EQ(0, add(1, -1));
}