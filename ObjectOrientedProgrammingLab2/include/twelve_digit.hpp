#pragma once

#include "array.hpp"

class TwelveDigit {
  private:
    unsigned char c;
    int charToValue(unsigned char ch) const;
    unsigned char valueToChar(int value) const;

  public:
    TwelveDigit();

    TwelveDigit(unsigned char new_sign);

    TwelveDigit(const TwelveDigit &other);

    TwelveDigit &operator=(const TwelveDigit &other);

    TwelveDigit operator+(const TwelveDigit &other) const;

    TwelveDigit operator-(const TwelveDigit &other) const;

    TwelveDigit &operator+=(const TwelveDigit &other);

    TwelveDigit &operator-=(const TwelveDigit &other);

    TwelveDigit operator+(unsigned char ch) const;

    TwelveDigit operator-(unsigned char ch) const;

    TwelveDigit &operator+=(unsigned char ch);

    TwelveDigit &operator-=(unsigned char ch);

    bool sumBiggerOrEqualTwelve(const TwelveDigit &other);

    bool diffLessThanZero(const TwelveDigit &subtrahend);

    bool operator==(const TwelveDigit &other) const;

    bool operator!=(const TwelveDigit &other) const;

    bool operator<(const TwelveDigit &other) const;

    bool operator<=(const TwelveDigit &other) const;

    bool operator>(const TwelveDigit &other) const;

    bool operator>=(const TwelveDigit &other) const;

    friend std::ostream &operator<<(std::ostream &out, const TwelveDigit &d);

    void setChar(unsigned char c);

    unsigned char getChar() const;
};
