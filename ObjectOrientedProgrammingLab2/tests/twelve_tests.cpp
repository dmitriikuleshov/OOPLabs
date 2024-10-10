#include "twelve.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

TEST(TwelveTest, DefaultConstructor) {
    Twelve t;
    ASSERT_EQ(t.toString(), "0");
}

TEST(TwelveTest, Base10Constructor) {
    Twelve t1(0);
    ASSERT_EQ(t1.toString(), "0");

    Twelve t2(10);
    ASSERT_EQ(t2.toString(), "A");

    Twelve t3(144);
    ASSERT_EQ(t3.toString(), "100");
}

TEST(TwelveTest, SizeDigitConstructor) {
    Twelve t(3, 'A');
    ASSERT_EQ(t.toString(), "AAA");
}

TEST(TwelveTest, InitializerListConstructor) {
    Twelve t({'1', '2', 'A'});
    ASSERT_EQ(t.toString(), "12A");
}

TEST(TwelveTest, StringConstructor) {
    Twelve t("12A");
    ASSERT_EQ(t.toString(), "12A");
}

TEST(TwelveTest, CopyConstructor) {
    Twelve t1("12A");
    Twelve t2(t1);
    ASSERT_EQ(t2.toString(), "12A");
}

TEST(TwelveTest, MoveConstructor) {
    Twelve t1("12A");
    Twelve t2(std::move(t1));
    ASSERT_EQ(t2.toString(), "12A");
}

TEST(TwelveTest, CopyAssignment) {
    Twelve t1("12A");
    Twelve t2;
    t2 = t1;
    ASSERT_EQ(t2.toString(), "12A");
}

TEST(TwelveTest, MoveAssignment) {
    Twelve t1("12A");
    Twelve t2;
    t2 = std::move(t1);
    ASSERT_EQ(t2.toString(), "12A");
}

// operator+=
void runPlusEqualTest(std::string first_num_str, std::string second_num_str,
                      std::string expected_result_str) {
    Twelve first_num(first_num_str);
    Twelve second_num(second_num_str);
    first_num += second_num;
    ASSERT_EQ(first_num, Twelve(expected_result_str));

    Twelve first_num1(first_num_str);
    Twelve second_num1(second_num_str);
    first_num1 += second_num1;
    ASSERT_EQ(first_num1, Twelve(expected_result_str));

    // Testing the commutativity of addition
    ASSERT_EQ(first_num, first_num1);
}

TEST(PlusEqualTest, PlusEqualTest1) { runPlusEqualTest("A3B", "45", "A84"); }

TEST(PlusEqualTest, PlusEqualTest2) { runPlusEqualTest("A3B", "0", "A3B"); }

TEST(PlusEqualTest, PlusEqualTest3) { runPlusEqualTest("0", "0", "0"); }

TEST(PlusEqualTest, PlusEqualTest4) { runPlusEqualTest("123", "456", "579"); }

TEST(PlusEqualTest, PlusEqualTest5) { runPlusEqualTest("B", "B", "1A"); }

TEST(PlusEqualTest, PlusEqualTest6) { runPlusEqualTest("BA", "BA", "1B8"); }

// operator -=
void runMinusEqualTest(std::string minued_str, std::string subtrahend_str,
                       std::string expected_difference_str) {
    Twelve minued(minued_str);
    Twelve subtrahend(subtrahend_str);
    minued -= subtrahend;
    ASSERT_EQ(minued, Twelve(expected_difference_str));
}

TEST(MinusEqualTest, MinusEqualTest1) { runMinusEqualTest("A84", "45", "A3B"); }

TEST(MinusEqualTest, MinusEqualTest2) { runMinusEqualTest("A3B", "0", "A3B"); }

TEST(MinusEqualTest, MinusEqualTest3) { runMinusEqualTest("0", "0", "0"); }

TEST(MinusEqualTest, MinusEqualTest4) {
    runMinusEqualTest("579", "456", "123");
}

TEST(MinusEqualTest, MinusEqualTest5) { runMinusEqualTest("1A", "B", "B"); }

TEST(MinusEqualTest, MinusEqualTest6) { runMinusEqualTest("1B8", "BA", "BA"); }

void runMinusEqualUnderflowTest(std::string minued_str,
                                std::string subtrahend_str) {
    Twelve minued(minued_str);
    Twelve subtrahend(subtrahend_str);
    try {
        minued -= subtrahend;
    } catch (std::underflow_error e) {
        ASSERT_TRUE(true);
    } catch (...) {
        FAIL() << "Expected std::invalid_argument\n";
    }
}

TEST(MinusEqualUnderflowTest, MinusEqualUnderflowTest1) {
    runMinusEqualUnderflowTest("45", "A84");
}

TEST(MinusEqualUnderflowTest, MinusEqualUnderflowTest2) {
    runMinusEqualUnderflowTest("0", "A3B");
}

TEST(MinusEqualUnderflowTest, MinusEqualUnderflowTest3) {
    runMinusEqualUnderflowTest("0", "1");
}

TEST(MinusEqualUnderflowTest, MinusEqualUnderflowTest4) {
    runMinusEqualUnderflowTest("456", "579");
}

TEST(MinusEqualUnderflowTest, MinusEqualUnderflowTest5) {
    runMinusEqualUnderflowTest("B", "1A");
}

TEST(MinusEqualUnderflowTest, MinusEqualUnderflowTest6) {
    runMinusEqualUnderflowTest("BA", "1B8");
}

// operator +
void runPlusTest(std::string first_num_str, std::string second_num_str,
                 std::string expected_result_str) {
    Twelve first_num(first_num_str);
    Twelve second_num(second_num_str);
    Twelve result = first_num + second_num;
    ASSERT_EQ(result, Twelve(expected_result_str));

    // Testing the commutativity of addition
    Twelve result1 = second_num + first_num;
    ASSERT_EQ(result1, Twelve(expected_result_str));
}

TEST(PlusTest, PlusTest1) { runPlusTest("A3B", "45", "A84"); }

TEST(PlusTest, PlusTest2) { runPlusTest("A3B", "0", "A3B"); }

TEST(PlusTest, PlusTest3) { runPlusTest("0", "0", "0"); }

TEST(PlusTest, PlusTest4) { runPlusTest("123", "456", "579"); }

TEST(PlusTest, PlusTest5) { runPlusTest("B", "B", "1A"); }

TEST(PlusTest, PlusTest6) { runPlusTest("BA", "BA", "1B8"); }

// operator -
void runMinusTest(std::string minued_str, std::string subtrahend_str,
                  std::string expected_difference_str) {
    Twelve minued(minued_str);
    Twelve subtrahend(subtrahend_str);
    Twelve result = minued - subtrahend;
    ASSERT_EQ(result, Twelve(expected_difference_str));
}

TEST(MinusTest, MinusTest1) { runMinusTest("A84", "45", "A3B"); }

TEST(MinusTest, MinusTest2) { runMinusTest("A3B", "0", "A3B"); }

TEST(MinusTest, MinusTest3) { runMinusTest("0", "0", "0"); }

TEST(MinusTest, MinusTest4) { runMinusTest("579", "456", "123"); }

TEST(MinusTest, MinusTest5) { runMinusTest("1A", "B", "B"); }

TEST(MinusTest, MinusTest6) { runMinusTest("1B8", "BA", "BA"); }

void runMinusUnderflowTest(std::string minued_str, std::string subtrahend_str) {
    Twelve minued(minued_str);
    Twelve subtrahend(subtrahend_str);
    try {
        Twelve result = minued - subtrahend;
    } catch (std::underflow_error e) {
        ASSERT_TRUE(true);
    } catch (...) {
        FAIL() << "Expected std::invalid_argument\n";
    }
}

TEST(MinusUnderflowTest, MinusUnderflowTest1) {
    runMinusUnderflowTest("45", "A84");
}

TEST(MinusUnderflowTest, MinusUnderflowTest2) {
    runMinusUnderflowTest("0", "A3B");
}

TEST(MinusUnderflowTest, MinusUnderflowTest3) {
    runMinusUnderflowTest("0", "1");
}

TEST(MinusUnderflowTest, MinusUnderflowTest4) {
    runMinusUnderflowTest("456", "579");
}

TEST(MinusUnderflowTest, MinusUnderflowTest5) {
    runMinusUnderflowTest("B", "1A");
}

TEST(MinusUnderflowTest, MinusUnderflowTest6) {
    runMinusUnderflowTest("BA", "1B8");
}

// Comparison
TEST(ComparisonTest, ComparisonTest1) {
    Twelve bigger_num("BBB");
    Twelve smaller_num("AAA");
    ASSERT_TRUE(bigger_num > smaller_num);
    ASSERT_TRUE(smaller_num < bigger_num);
    ASSERT_FALSE(bigger_num < smaller_num);
    ASSERT_FALSE(smaller_num > bigger_num);

    ASSERT_FALSE(bigger_num == smaller_num);
    ASSERT_FALSE(smaller_num == bigger_num);
    ASSERT_TRUE(bigger_num == bigger_num);
    ASSERT_TRUE(smaller_num == smaller_num);
}

TEST(ComparisonTest, ComparisonTest2) {
    Twelve bigger_num("BBB");
    Twelve smaller_num("AAA");
    ASSERT_TRUE(bigger_num >= smaller_num);
    ASSERT_TRUE(smaller_num <= bigger_num);
    ASSERT_FALSE(bigger_num <= smaller_num);
    ASSERT_FALSE(smaller_num >= bigger_num);

    ASSERT_FALSE(bigger_num == smaller_num);
    ASSERT_FALSE(smaller_num == bigger_num);
    ASSERT_TRUE(bigger_num == bigger_num);
    ASSERT_TRUE(smaller_num == smaller_num);
}

TEST(ComparisonTest, ComparisonTes3) {
    Twelve zero1("0");
    Twelve zero2("0");
    ASSERT_FALSE(zero1 > zero2);
    ASSERT_FALSE(zero2 < zero1);
    ASSERT_FALSE(zero1 < zero2);
    ASSERT_FALSE(zero2 > zero1);

    ASSERT_TRUE(zero1 >= zero2);
    ASSERT_TRUE(zero2 <= zero1);
    ASSERT_TRUE(zero1 <= zero2);
    ASSERT_TRUE(zero2 >= zero1);

    ASSERT_TRUE(zero1 == zero2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}