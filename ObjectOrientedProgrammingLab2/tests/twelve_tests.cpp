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
void runPlusEqualTest(std::string firstNumValue, std::string secondNumValue,
                      std::string expectedResultValue) {
    Twelve firstNum(firstNumValue);
    Twelve secondNum(secondNumValue);
    firstNum += secondNum;
    ASSERT_EQ(firstNum, Twelve(expectedResultValue));

    Twelve firstNum1(firstNumValue);
    Twelve secondNum1(secondNumValue);
    firstNum1 += secondNum1;
    ASSERT_EQ(firstNum1, Twelve(expectedResultValue));

    // Testing the commutativity of addition
    ASSERT_EQ(firstNum, firstNum1);
}

TEST(PlusEqualTest, PlusEqualTest1) { runPlusEqualTest("A3B", "45", "A84"); }

TEST(PlusEqualTest, PlusEqualTest2) { runPlusEqualTest("A3B", "0", "A3B"); }

TEST(PlusEqualTest, PlusEqualTest3) { runPlusEqualTest("0", "0", "0"); }

TEST(PlusEqualTest, PlusEqualTest4) { runPlusEqualTest("123", "456", "579"); }

TEST(PlusEqualTest, PlusEqualTest5) { runPlusEqualTest("B", "B", "1A"); }

TEST(PlusEqualTest, PlusEqualTest6) { runPlusEqualTest("BA", "BA", "1B8"); }

// operator -=
void runMinusEqualTest(std::string minuedValue, std::string subtrahendValue,
                       std::string expectedDifferenceValue) {
    Twelve minued(minuedValue);
    Twelve subtrahend(subtrahendValue);
    minued -= subtrahend;
    ASSERT_EQ(minued, Twelve(expectedDifferenceValue));
}

TEST(MinusEqualTest, MinusEqualTest1) { runMinusEqualTest("A84", "45", "A3B"); }

TEST(MinusEqualTest, MinusEqualTest2) { runMinusEqualTest("A3B", "0", "A3B"); }

TEST(MinusEqualTest, MinusEqualTest3) { runMinusEqualTest("0", "0", "0"); }

TEST(MinusEqualTest, MinusEqualTest4) {
    runMinusEqualTest("579", "456", "123");
}

TEST(MinusEqualTest, MinusEqualTest5) { runMinusEqualTest("1A", "B", "B"); }

TEST(MinusEqualTest, MinusEqualTest6) { runMinusEqualTest("1B8", "BA", "BA"); }

void runMinusEqualUnderflowTest(std::string minuedValue,
                                std::string subtrahendValue) {
    Twelve minued(minuedValue);
    Twelve subtrahend(subtrahendValue);
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
void runPlusTest(std::string firstNumValue, std::string secondNumValue,
                 std::string expectedResultValue) {
    Twelve firstNum(firstNumValue);
    Twelve secondNum(secondNumValue);
    Twelve result = firstNum + secondNum;
    ASSERT_EQ(result, Twelve(expectedResultValue));

    // Testing the commutativity of addition
    Twelve result1 = secondNum + firstNum;
    ASSERT_EQ(result1, Twelve(expectedResultValue));
}

TEST(PlusTest, PlusTest1) { runPlusTest("A3B", "45", "A84"); }

TEST(PlusTest, PlusTest2) { runPlusTest("A3B", "0", "A3B"); }

TEST(PlusTest, PlusTest3) { runPlusTest("0", "0", "0"); }

TEST(PlusTest, PlusTest4) { runPlusTest("123", "456", "579"); }

TEST(PlusTest, PlusTest5) { runPlusTest("B", "B", "1A"); }

TEST(PlusTest, PlusTest6) { runPlusTest("BA", "BA", "1B8"); }

// operator -
void runMinusTest(std::string minuedValue, std::string subtrahendValue,
                  std::string expectedDifferenceValue) {
    Twelve minued(minuedValue);
    Twelve subtrahend(subtrahendValue);
    Twelve result = minued - subtrahend;
    ASSERT_EQ(result, Twelve(expectedDifferenceValue));
}

TEST(MinusTest, MinusTest1) { runMinusTest("A84", "45", "A3B"); }

TEST(MinusTest, MinusTest2) { runMinusTest("A3B", "0", "A3B"); }

TEST(MinusTest, MinusTest3) { runMinusTest("0", "0", "0"); }

TEST(MinusTest, MinusTest4) { runMinusTest("579", "456", "123"); }

TEST(MinusTest, MinusTest5) { runMinusTest("1A", "B", "B"); }

TEST(MinusTest, MinusTest6) { runMinusTest("1B8", "BA", "BA"); }

void runMinusUnderflowTest(std::string minuedValue,
                           std::string subtrahendValue) {
    Twelve minued(minuedValue);
    Twelve subtrahend(subtrahendValue);
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
    Twelve biggerNum("BBB");
    Twelve smallerNum("AAA");
    ASSERT_TRUE(biggerNum > smallerNum);
    ASSERT_TRUE(smallerNum < biggerNum);
    ASSERT_FALSE(biggerNum < smallerNum);
    ASSERT_FALSE(smallerNum > biggerNum);

    ASSERT_FALSE(biggerNum == smallerNum);
    ASSERT_FALSE(smallerNum == biggerNum);
    ASSERT_TRUE(biggerNum == biggerNum);
    ASSERT_TRUE(smallerNum == smallerNum);
}

TEST(ComparisonTest, ComparisonTest2) {
    Twelve biggerNum("BBB");
    Twelve smallerNum("AAA");
    ASSERT_TRUE(biggerNum >= smallerNum);
    ASSERT_TRUE(smallerNum <= biggerNum);
    ASSERT_FALSE(biggerNum <= smallerNum);
    ASSERT_FALSE(smallerNum >= biggerNum);

    ASSERT_FALSE(biggerNum == smallerNum);
    ASSERT_FALSE(smallerNum == biggerNum);
    ASSERT_TRUE(biggerNum == biggerNum);
    ASSERT_TRUE(smallerNum == smallerNum);
}

TEST(ComparisonTest, ComparisonTes3) {
    Twelve firstNum("0");
    Twelve secondNum("0");
    ASSERT_FALSE(firstNum > secondNum);
    ASSERT_FALSE(secondNum < firstNum);
    ASSERT_FALSE(firstNum < secondNum);
    ASSERT_FALSE(secondNum > firstNum);

    ASSERT_TRUE(firstNum >= secondNum);
    ASSERT_TRUE(secondNum <= firstNum);
    ASSERT_TRUE(firstNum <= secondNum);
    ASSERT_TRUE(secondNum >= firstNum);

    ASSERT_TRUE(firstNum == secondNum);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}