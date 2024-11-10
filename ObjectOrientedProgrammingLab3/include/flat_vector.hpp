#pragma once

#include <cmath>
#include <iostream>

struct flat_vector {
    // Variables
    double x;
    double y;

    // Constructors
    flat_vector() noexcept;
    flat_vector(double x, double y) noexcept;

    //  Algebra operators

    flat_vector operator+(const flat_vector &other) const noexcept;
    flat_vector &operator+=(const flat_vector &other) noexcept;

    flat_vector operator-(const flat_vector &other) const noexcept;
    flat_vector &operator-=(const flat_vector &other) noexcept;

    flat_vector operator-() const noexcept;

    flat_vector operator*(const double &labmda) const noexcept;
    flat_vector &operator*=(const double &labmda) noexcept;

    double dot(const flat_vector &other) const noexcept;

    double len() const noexcept;

    // polar angle in [-pi; pi]
    double polar_angle() const noexcept;

    friend flat_vector &operator~(flat_vector &v) noexcept;

    friend flat_vector operator*(const double &lambda,
                                 const flat_vector &v) noexcept;

    // Comparation operators

    bool operator==(const flat_vector &other) const noexcept;

    bool operator!=(const flat_vector &other) const noexcept;
};

flat_vector operator*(double lambda, const flat_vector &v) noexcept;

double triangle_area(const flat_vector &a, const flat_vector &b) noexcept;

double angle(const flat_vector &a, const flat_vector &b) noexcept;

bool cmp_by_polar_angle(const flat_vector &a, const flat_vector &b) noexcept;

bool cmp_by_len(const flat_vector &a, const flat_vector &b) noexcept;

std::istream &operator>>(std::istream &in, flat_vector &f);

std::ostream &operator<<(std::ostream &out, const flat_vector &f);

bool double_eq_zero(double d, double eps = 10e-9) noexcept;

// Two lines: l1 of a&b, l2 of c&d.
// Throws exception if straight don't cross
flat_vector intersection(const flat_vector &a, const flat_vector &b,
                         const flat_vector &c, const flat_vector &d);
