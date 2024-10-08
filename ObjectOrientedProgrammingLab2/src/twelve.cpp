#include "twelve.hpp"
#include "twelve_digit.hpp"
#include <iostream>
#include <unistd.h>

// Initialize
Twelve::Twelve() { digits.push_back('0'); }

// Initialize using string
Twelve::Twelve(const std::string &str) { initializeFromString(str); }

// Initialize using Base10 value
Twelve::Twelve(unsigned int n) {
    if (n == 0) {
        digits.push_back('0');
    } else {
        std::string base12;
        const char digits[] = {'0', '1', '2', '3', '4', '5',
                               '6', '7', '8', '9', 'A', 'B'};
        while (n > 0) {
            unsigned int remainder = n % 12;
            base12 = digits[remainder] + base12;
            n /= 12;
        }
        initializeFromString(base12);
    }
}

// Initialize using size and digit
Twelve::Twelve(size_t size, const TwelveDigit &digit) {
    for (size_t i = 0; i < size; ++i) {
        digits.push_back(digit);
    }
    removeInsignificantZeros(*this);
}

// Initialize using initializer list
Twelve::Twelve(const std::initializer_list<TwelveDigit> &t) {
    for (auto it = t.end() - 1; it >= t.begin(); --it) {
        digits.push_back(*it);
    }
    removeInsignificantZeros(*this);
}

// Copy Constructor
Twelve::Twelve(const Twelve &other) { copy(other); }

// Move constructor
Twelve::Twelve(Twelve &&other) noexcept { digits = other.digits; }

// Copy Assignment
Twelve &Twelve::operator=(const Twelve &other) {
    copy(other);
    return *this;
}

// Move Assignment
Twelve &Twelve::operator=(Twelve &&other) {
    digits = other.digits;
    return *this;
}

void Twelve::initializeFromString(const std::string &str) {
    for (int i = str.length() - 1; i >= 0; --i) {
        digits.push_back(str[i]);
    }
    removeInsignificantZeros(*this);
}

std::string Twelve::toString() const {
    std::string num_string;
    for (int j = digits.size() - 1; j >= 0; --j) {
        num_string += digits[j].getChar();
    }
    return num_string;
}

size_t Twelve::length() const { return digits.size(); }

void Twelve::removeInsignificantZeros(Twelve &num) {
    for (int j = num.digits.size() - 1; j >= 1; --j) {
        if (num.digits[j] != TwelveDigit('0')) {
            break;
        }
        num.digits.pop_back();
    }
}

void Twelve::copy(const Twelve &other) {
    digits.clear();
    for (size_t i = 0; i < other.digits.size(); ++i) {
        digits.push_back(other.digits[i]);
    }
}

// Comparison
bool Twelve::operator<(const Twelve &other) const {
    if (digits.size() == other.digits.size()) {
        for (size_t i = digits.size() - 1; i > 0; --i) {
            if (digits[i] < other.digits[i]) {
                return true;
            }
        }
        return false;
    } else {
        return digits.size() < other.digits.size();
    }
}

bool Twelve::operator==(const Twelve &other) const {
    if (digits.size() == other.digits.size()) {
        for (size_t i = 0; i < digits.size(); ++i) {
            if (digits[i] != other.digits[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool Twelve::operator!=(const Twelve &other) const { return !(*this == other); }

bool Twelve::operator<=(const Twelve &other) const {
    return (*this < other) || (*this == other);
}

bool Twelve::operator>(const Twelve &other) const { return !(*this <= other); }

bool Twelve::operator>=(const Twelve &other) const { return !(*this < other); }

// Arithmetic
Twelve &Twelve::operator+=(const Twelve &other) {

    Twelve biggerNum = (*this <= other ? other : *this);
    Twelve smallerNum = (*this > other ? other : *this);
    Twelve inMind;
    Twelve result;

    do {
        inMind = Twelve("0");
        result.digits.clear();
        for (size_t i = 0; i < biggerNum.digits.size(); ++i) {
            if (i >= smallerNum.digits.size()) {
                smallerNum.digits.push_back('0');
            }
            if (biggerNum.digits[i].sumBiggerOrEqualTwelve(
                    smallerNum.digits[i])) {
                inMind.digits.push_back('1');
            } else {
                inMind.digits.push_back('0');
            }
            result.digits.push_back(smallerNum.digits[i] + biggerNum.digits[i]);
        }
        removeInsignificantZeros(inMind);
        removeInsignificantZeros(result);
        biggerNum = (inMind <= result ? result : inMind);
        smallerNum = (inMind > result ? result : inMind);
    } while (inMind > Twelve("0"));

    copy(result);
    return *this;
}

Twelve Twelve::operator+(const Twelve &other) const {
    Twelve temp = *this;
    temp += other;
    return temp;
}

Twelve &Twelve::operator-=(const Twelve &other) {
    if (*this < other) {
        throw std::underflow_error("Subtraction results in negative value "
                                   "for unsigned Base12 number");
    }
    Twelve biggerNum = *this;
    Twelve smallerNum = other;
    Twelve inMind;
    Twelve result;

    do {
        inMind = Twelve("0");
        result.digits.clear();
        for (size_t i = 0; i < biggerNum.digits.size(); ++i) {
            if (i >= smallerNum.digits.size()) {
                smallerNum.digits.push_back('0');
            }
            if (biggerNum.digits[i].diffLessThanZero(smallerNum.digits[i])) {
                inMind.digits.push_back('1');
            } else {
                inMind.digits.push_back('0');
            }
            result.digits.push_back(biggerNum.digits[i] - smallerNum.digits[i]);
        }
        removeInsignificantZeros(inMind);
        removeInsignificantZeros(result);
        biggerNum = result;
        smallerNum = inMind;
    } while (inMind > Twelve("0"));

    copy(result);
    return *this;
}

Twelve Twelve::operator-(const Twelve &other) const {
    Twelve temp = *this;
    temp -= other;
    return temp;
}

std::ostream &operator<<(std::ostream &out, const Twelve &num) {
    for (int i = num.digits.size() - 1; i >= 0; --i) {
        out << num.digits[i].getChar();
    }
    return out;
}