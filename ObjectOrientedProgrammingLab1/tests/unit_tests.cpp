#include "to_binary_string.h"
#include <gtest/gtest.h>
#include <string>

TEST(to_binary_string_test1, test1) {
    int num = 1;
    std::string expected = "00000000000000000000000000000001";
    std::string result = to_binary_string(num);
    EXPECT_EQ(result, expected);
}

TEST(to_binary_string_test2, test0) {
    int num = 0;
    std::string expected = "00000000000000000000000000000000";
    std::string result = to_binary_string(num);
    EXPECT_EQ(result, expected);
}

TEST(to_binary_string_test3, test255) {
    int num = 255;
    std::string expected = "00000000000000000000000011111111";
    std::string result = to_binary_string(num);
    EXPECT_EQ(result, expected);
}

TEST(to_binary_string_test4, test_max_uint32) {
    int num = 4294967295;
    std::string expected = "11111111111111111111111111111111";
    std::string result = to_binary_string(num);
    EXPECT_EQ(result, expected);
}

TEST(to_binary_string_test5, test_random) {
    int num = 1024;
    std::string expected = "00000000000000000000010000000000";
    std::string result = to_binary_string(num);
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
