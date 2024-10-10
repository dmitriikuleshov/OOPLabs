#include "twelve_digit.hpp"
#include <gtest/gtest.h>
#include <string>

// Default Constructor
TEST(TwelveDigitConstructor, DefaultConstructorTest1) {
    TwelveDigit digit;
    ASSERT_EQ(digit.getChar(), '0');
}

// Constructor
TEST(TwelveDigitConstructor, ConstructorTest1) {
    TwelveDigit digit('2');
    ASSERT_EQ(digit.getChar(), '2');
}

TEST(TwelveDigitConstructor, ConstructorTest2) {
    TwelveDigit digit('0');
    ASSERT_EQ(digit.getChar(), '0');
}

TEST(TwelveDigitConstructor, ConstructorTest3) {
    TwelveDigit digit('9');
    ASSERT_EQ(digit.getChar(), '9');
}

TEST(TwelveDigitConstructor, ConstructorTest4) {
    TwelveDigit digit('A');
    ASSERT_EQ(digit.getChar(), 'A');
}

TEST(TwelveDigitConstructor, ConstructorTest5) {
    TwelveDigit digit('B');
    ASSERT_EQ(digit.getChar(), 'B');
}

TEST(TwelveDigitConstructor, ConstructorInvalidArgumentTest1) {
    try {
        TwelveDigit digit(42);
        FAIL() << "Expected std::invalid_argument\n";
    } catch (std::invalid_argument e) {
        ASSERT_TRUE(true);
    } catch (...) {
        FAIL() << "Expected std::invalid_argument\n";
    }
}

TEST(TwelveDigitConstructor, ConstructorInvalidArgumentTest2) {
    try {
        TwelveDigit digit('C');
        FAIL() << "Expected std::invalid_argument\n";
    } catch (std::invalid_argument e) {
        ASSERT_TRUE(true);
    } catch (...) {
        FAIL() << "Expected std::invalid_argument\n";
    }
}

// Copy Constructor
TEST(TwelveDigitConstructor, CopyConstructorTest1) {
    TwelveDigit digit1('7');
    TwelveDigit digit2(digit1);
    ASSERT_TRUE(digit1.getChar() == digit2.getChar());
}

TEST(TwelveDigitConstructor, CopyConstructorTest2) {
    TwelveDigit digit1('A');
    TwelveDigit digit2(digit1);
    ASSERT_TRUE(digit1.getChar() == digit2.getChar());
}

TEST(TwelveDigitConstructor, CopyConstructorTest3) {
    TwelveDigit digit1('B');
    TwelveDigit digit2(digit1);
    ASSERT_TRUE(digit1.getChar() == digit2.getChar());
}

// Arithmetics

// operator +=
void runPlusEqualTest(unsigned char digit_value, unsigned char increase,
                      unsigned char expect) {
    TwelveDigit digit(digit_value);
    digit += increase;
    ASSERT_EQ(digit.getChar(), expect);

    TwelveDigit digit1(digit_value);
    TwelveDigit digit2(increase);
    digit1 += digit2;
    ASSERT_EQ(digit1.getChar(), expect);
}

TEST(TwelveDigitAriphmeticOperator, PlusEqualOperatorTest1) {
    runPlusEqualTest('2', '2', '4');
}

TEST(TwelveDigitAriphmeticOperator, PlusEqualOperatorTest2) {
    runPlusEqualTest('6', '4', 'A');
}

TEST(TwelveDigitAriphmeticOperator, PlusEqualOperatorTest3) {
    runPlusEqualTest('8', '8', '4');
}

TEST(TwelveDigitAriphmeticOperator, PlusEqualOperatorTest4) {
    runPlusEqualTest('0', 'A', 'A');
}

TEST(TwelveDigitAriphmeticOperator, PlusEqualOperatorTest5) {
    runPlusEqualTest('5', '0', '5');
}

TEST(TwelveDigitAriphmeticOperator, PlusEqualOperatorTest6) {
    runPlusEqualTest('0', 'B', 'B');
}

TEST(TwelveDigitAriphmeticOperator, PlusEqualOperatorTest7) {
    runPlusEqualTest('9', '2', 'B');
}

// operator -=
void runMinusEqualTest(unsigned char digit_value, unsigned char decrease,
                       unsigned char expect) {
    TwelveDigit digit(digit_value);
    digit -= decrease;
    ASSERT_EQ(digit.getChar(), expect);

    TwelveDigit digit1(digit_value);
    TwelveDigit digit2(decrease);
    digit1 -= digit2;
    ASSERT_EQ(digit1.getChar(), expect);
}

TEST(TwelveDigitAriphmeticOperator, MinusEqualOperatorTest1) {
    runMinusEqualTest('4', '2', '2');
}

TEST(TwelveDigitAriphmeticOperator, MinusEqualOperatorTest2) {
    runMinusEqualTest('A', '4', '6');
}

TEST(TwelveDigitAriphmeticOperator, MinusEqualOperatorTest3) {
    runMinusEqualTest('4', '8', '8');
}

TEST(TwelveDigitAriphmeticOperator, MinusEqualOperatorTest4) {
    runMinusEqualTest('A', 'A', '0');
}

TEST(TwelveDigitAriphmeticOperator, MinusEqualOperatorTest5) {
    runMinusEqualTest('5', '0', '5');
}

TEST(TwelveDigitAriphmeticOperator, MinusEqualOperatorTest6) {
    runMinusEqualTest('B', 'B', '0');
}

TEST(TwelveDigitAriphmeticOperator, MinusEqualOperatorTest7) {
    runMinusEqualTest('B', '2', '9');
}

// operator +
void runPlusTest(unsigned char digit1_value, unsigned char digit2_value,
                 unsigned char expect) {
    TwelveDigit digit1(digit2_value);
    TwelveDigit digit2(digit1_value);
    TwelveDigit result = digit1 + digit2;
    ASSERT_EQ(result.getChar(), expect);
}

TEST(TwelveDigitAriphmeticOperator, PlusOperatorTest1) {
    runPlusTest('2', '2', '4');
}

TEST(TwelveDigitAriphmeticOperator, PlusOperatorTest2) {
    runPlusTest('6', '4', 'A');
}

TEST(TwelveDigitAriphmeticOperator, PlusOperatorTest3) {
    runPlusTest('8', '8', '4');
}

TEST(TwelveDigitAriphmeticOperator, PlusOperatorTest4) {
    runPlusTest('0', 'A', 'A');
}

TEST(TwelveDigitAriphmeticOperator, PlusOperatorTest5) {
    runPlusTest('5', '0', '5');
}

TEST(TwelveDigitAriphmeticOperator, PlusOperatorTest6) {
    runPlusTest('0', 'B', 'B');
}

TEST(TwelveDigitAriphmeticOperator, PlusOperatorTest7) {
    runPlusTest('9', '2', 'B');
}

// operator -
void runMinusTest(unsigned char digit1_value, unsigned char digit2_value,
                  unsigned char expect) {
    TwelveDigit digit1(digit1_value);
    TwelveDigit digit2(digit2_value);
    TwelveDigit result = digit1 - digit2;
    ASSERT_EQ(result.getChar(), expect);
}

TEST(TwelveDigitAriphmeticOperator, MinusOperatorTest1) {
    runMinusTest('4', '2', '2');
}

TEST(TwelveDigitAriphmeticOperator, MinusOperatorTest2) {
    runMinusTest('A', '4', '6');
}

TEST(TwelveDigitAriphmeticOperator, MinusOperatorTest3) {
    runMinusTest('4', '8', '8');
}

TEST(TwelveDigitAriphmeticOperator, MinusOperatorTest4) {
    runMinusTest('A', 'A', '0');
}

TEST(TwelveDigitAriphmeticOperator, MinusOperatorTest5) {
    runMinusTest('5', '0', '5');
}

TEST(TwelveDigitAriphmeticOperator, MinusOperatorTest6) {
    runMinusTest('B', 'B', '0');
}

TEST(TwelveDigitAriphmeticOperator, MinusOperatorTest7) {
    runMinusTest('B', '2', '9');
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}