#include "../src/to_binary_string.cpp"
#include <gtest/gtest.h>
#include <string>

TEST(ToBinaryStringTest, Test1) {
    EXPECT_EQ(to_binary_string(1), "00000000000000000000000000000001");
}

TEST(ToBinaryStringTest, Test0) {
    EXPECT_EQ(to_binary_string(0), "00000000000000000000000000000000");
}

TEST(ToBinaryStringTest, Test255) {
    EXPECT_EQ(to_binary_string(255), "00000000000000000000000011111111");
}

TEST(ToBinaryStringTest, TestMaxUInt32) {
    EXPECT_EQ(to_binary_string(4294967295), "11111111111111111111111111111111");
}

TEST(ToBinaryStringTest, TestRandom) {
    EXPECT_EQ(to_binary_string(1024), "00000000000000000000010000000000");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
