#pragma once

#include "array.hpp"
#include "twelve_digit.hpp"
#include <string>

class Twelve {
  private:
    Array<TwelveDigit> digits;

  public:
    Twelve();

    Twelve(unsigned int n);

    Twelve(size_t size, const TwelveDigit &digit);

    Twelve(const std::initializer_list<TwelveDigit> &t);

    Twelve(const std::string &str);

    Twelve(const Twelve &other);

    Twelve(Twelve &&other) noexcept;

    size_t length() const;

    std::string toString() const;

    void initializeFromString(const std::string &str);

    void copy(const Twelve &other);

    void removeInsignificantZeros(Twelve &num);

    Twelve &operator=(const Twelve &other);

    Twelve &operator=(Twelve &&other);

    // Arithmetic

    Twelve operator+(const Twelve &other) const;

    Twelve &operator+=(const Twelve &other);

    Twelve operator-(const Twelve &other) const;

    Twelve &operator-=(const Twelve &other);

    // Comparation

    bool operator==(const Twelve &other) const;

    bool operator!=(const Twelve &other) const;

    bool operator<(const Twelve &other) const;

    bool operator<=(const Twelve &other) const;

    bool operator>(const Twelve &other) const;

    bool operator>=(const Twelve &other) const;

    // Friends
  protected:
    friend std::ostream &operator<<(std::ostream &out, const Twelve &num);
};