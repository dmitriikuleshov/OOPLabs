#include "twelve_digit.hpp"
#include "stdexcept"

TwelveDigit::TwelveDigit() : TwelveDigit('0') {}

TwelveDigit::TwelveDigit(unsigned char c) { setChar(c); }

TwelveDigit::TwelveDigit(const TwelveDigit &other) { *this = other; }

int TwelveDigit::charToValue(unsigned char ch) const {
    if (ch >= '0' && ch <= '9') {
        return ch - '0'; // '0' -> 0, '1' -> 1, ..., '9' -> 9
    } else if (ch == 'A') {
        return 10; // 'A' -> 10
    } else if (ch == 'B') {
        return 11; // 'B' -> 11
    } else {
        throw std::invalid_argument("Invalid character for base-12 system");
    }
}

unsigned char TwelveDigit::valueToChar(int value) const {
    if (value >= 0 && value <= 9) {
        return '0' + value; // 0 -> '0', 1 -> '1', ..., 9 -> '9'
    } else if (value == 10) {
        return 'A'; // 10 -> 'A'
    } else if (value == 11) {
        return 'B'; // 11 -> 'B'
    } else {
        throw std::invalid_argument("Invalid value for base-12 system");
    }
}

TwelveDigit &TwelveDigit::operator=(const TwelveDigit &other) {
    setChar(other.c);
    return *this;
}

TwelveDigit TwelveDigit::operator+(const TwelveDigit &other) const {
    TwelveDigit res = *this;
    return res += other;
}

TwelveDigit TwelveDigit::operator-(const TwelveDigit &other) const {
    TwelveDigit res = *this;
    return res -= other;
}

TwelveDigit &TwelveDigit::operator+=(const TwelveDigit &other) {
    return *this += other.c;
}

TwelveDigit &TwelveDigit::operator-=(const TwelveDigit &other) {
    return *this -= other.c;
}

TwelveDigit TwelveDigit::operator+(unsigned char ch) const {
    TwelveDigit res = *this;
    return res += ch;
}

TwelveDigit TwelveDigit::operator-(unsigned char ch) const {
    TwelveDigit res = *this;
    return res -= ch;
}

TwelveDigit &TwelveDigit::operator+=(unsigned char ch) {
    int current_value = charToValue(c);
    int add_value = charToValue(ch);
    int new_value = (current_value + add_value) % 12;
    c = valueToChar(new_value);
    return *this;
}

TwelveDigit &TwelveDigit::operator-=(unsigned char ch) {
    int current_value = charToValue(c);
    int sub_value = charToValue(ch);
    int new_value = (current_value - sub_value + 12) % 12;
    c = valueToChar(new_value);
    return *this;
}

bool TwelveDigit::sumBiggerOrEqualTwelve(const TwelveDigit &other) {
    int digit1_value = charToValue(c);
    int digit2_value = charToValue(other.getChar());
    return (digit1_value + digit2_value) >= 12;
}

bool TwelveDigit::diffLessThanZero(const TwelveDigit &subtrahend) {
    int minuent_value = charToValue(c);
    int subtrahend_value = charToValue(subtrahend.getChar());
    return (minuent_value - subtrahend_value) < 0;
}

bool TwelveDigit::operator==(const TwelveDigit &other) const {
    return this->c == other.c;
}

bool TwelveDigit::operator!=(const TwelveDigit &other) const {
    return !(*this == other);
}

bool TwelveDigit::operator<(const TwelveDigit &other) const {
    return this->c < other.c;
}

bool TwelveDigit::operator<=(const TwelveDigit &other) const {
    return (*this < other) || (*this == other);
}

bool TwelveDigit::operator>(const TwelveDigit &other) const {
    return !(*this <= other);
}

bool TwelveDigit::operator>=(const TwelveDigit &other) const {
    return !(*this < other);
}

std::ostream &operator<<(std::ostream &out, const TwelveDigit &digit) {
    out << digit.c;
    return out;
}

void TwelveDigit::setChar(unsigned char c) {
    if ('0' <= c && c <= '9') {
        this->c = c;
    } else if (0 <= c && c <= 9) {
        this->c = c + '0';
    } else if ('A' <= c && c <= 'B') {
        this->c = c;
    } else if ('a' <= c && c <= 'b') {
        this->c = c - 'a' + 'A';
    } else {
        throw std::invalid_argument(
            "No way to cast unsigned char to duodecimal digit\n");
    }
}

unsigned char TwelveDigit::getChar() const { return this->c; }
