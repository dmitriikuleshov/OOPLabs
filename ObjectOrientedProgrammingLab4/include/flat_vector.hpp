#pragma once

#include <cmath>
#include <iostream>
#include <memory>

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

#ifndef DOUBLE_EPS_DEFAULT
#define DOUBLE_EPS_DEFAULT 10e-9
#endif

template <Number T>
struct flat_vector : std::enable_shared_from_this<flat_vector<T>> {
    // Variables
    T x;
    T y;

    // Constructors
    flat_vector() noexcept;
    flat_vector(T x, T y) noexcept;

    //  Algebra operators

    flat_vector operator+(const flat_vector &other) const noexcept;
    flat_vector &operator+=(const flat_vector &other) noexcept;

    flat_vector operator-(const flat_vector &other) const noexcept;
    flat_vector &operator-=(const flat_vector &other) noexcept;

    flat_vector operator-() const noexcept;

    flat_vector operator*(const T &labmda) const noexcept;
    flat_vector &operator*=(const T &labmda) noexcept;

    T dot(const flat_vector &other) const noexcept;

    T len() const noexcept;

    // polar angle in [-pi; pi]
    T polar_angle() const noexcept;

    template <Number K>
    friend flat_vector<K> &operator~(flat_vector<K> &v) noexcept;

    template <Number K>
    friend flat_vector<K> operator*(const K &lambda,
                                    const flat_vector<K> &v) noexcept;

    // Comparation operators

    bool operator==(const flat_vector &other) const noexcept;

    bool operator!=(const flat_vector &other) const noexcept;
};

template <Number T>
flat_vector<T> operator*(T lambda, const flat_vector<T> &v) noexcept;

template <Number T>
T triangle_area(const flat_vector<T> &a, const flat_vector<T> &b) noexcept;

template <Number T>
T angle(const flat_vector<T> &a, const flat_vector<T> &b) noexcept;

template <Number T>
bool cmp_by_polar_angle(const flat_vector<T> &a,
                        const flat_vector<T> &b) noexcept;

template <Number T>
bool cmp_by_len(const flat_vector<T> &a, const flat_vector<T> &b) noexcept;

template <Number T>
std::istream &operator>>(std::istream &in, flat_vector<T> &f);

template <Number T>
std::ostream &operator<<(std::ostream &out, const flat_vector<T> &f);

template <Number T>
bool double_eq_zero(double d, double eps = DOUBLE_EPS_DEFAULT) noexcept;

// Two lines: l1 of a&b, l2 of c&d.
// Throws exception if straight don't cross
template <Number T>
flat_vector<T> intersection(const flat_vector<T> &a, const flat_vector<T> &b,
                            const flat_vector<T> &c, const flat_vector<T> &d);

template <Number T> flat_vector<T>::flat_vector() noexcept : x{}, y{} {}

template <Number T>
flat_vector<T>::flat_vector(T x, T y) noexcept : x(x), y(y) {}

template <Number T>
flat_vector<T>
flat_vector<T>::operator+(const flat_vector<T> &other) const noexcept {
    flat_vector<T> tmp = *this;
    return tmp += other;
}

template <Number T>
flat_vector<T> &
flat_vector<T>::operator+=(const flat_vector<T> &other) noexcept {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

template <Number T>
flat_vector<T>
flat_vector<T>::operator-(const flat_vector<T> &other) const noexcept {
    flat_vector<T> tmp = *this;
    return tmp -= other;
}

template <Number T>
flat_vector<T> &
flat_vector<T>::operator-=(const flat_vector<T> &other) noexcept {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

template <Number T> flat_vector<T> flat_vector<T>::operator-() const noexcept {
    flat_vector<T> tmp = *this;
    return ~tmp;
}

template <Number T>
flat_vector<T> flat_vector<T>::operator*(const T &lambda) const noexcept {
    flat_vector<T> tmp = *this;
    return tmp *= lambda;
}
template <Number T>
flat_vector<T> operator*(T lambda, const flat_vector<T> &v) noexcept {
    return v * lambda;
}
template <Number T>
flat_vector<T> &flat_vector<T>::operator*=(const T &lambda) noexcept {
    this->x *= lambda;
    this->y *= lambda;
    return *this;
}

template <Number T>
T flat_vector<T>::dot(const flat_vector<T> &other) const noexcept {
    return (this->x * other.x) + (this->y * other.y);
}

template <Number T> T flat_vector<T>::len() const noexcept {
    return sqrt(this->dot(*this));
}
template <Number T> T flat_vector<T>::polar_angle() const noexcept {
    if (x == 0 && y == 0) {
        return 0.0;
    } else {
        return atan2(y, x);
    }
}
template <Number T> flat_vector<T> &operator~(flat_vector<T> &v) noexcept {
    v.x = -v.x;
    v.y = -v.y;
    return v;
}

template <Number T>
bool flat_vector<T>::operator==(const flat_vector<T> &other) const noexcept {
    return (this->x == other.x) && (this->y == other.y);
}
template <Number T>
bool flat_vector<T>::operator!=(const flat_vector<T> &other) const noexcept {
    return !(*this == other);
}

template <Number T>
T triangle_area(const flat_vector<T> &a, const flat_vector<T> &b) noexcept {
    return abs(((a.x * b.y) - (a.y * b.x))) / 2.0;
}

template <Number T>
T angle(const flat_vector<T> &a, const flat_vector<T> &b) noexcept {
    T scalar = a.dot(b);
    if (scalar == 0) {
        return M_PI / 2;
    } else {
        return atan2(2.0 * triangle_area(a, b), scalar);
    }
}
template <Number T>
bool cmp_by_polar_angle(const flat_vector<T> &a,
                        const flat_vector<T> &b) noexcept {
    return a.polar_angle() < b.polar_angle();
}
template <Number T>
static bool cmp_by_len(const flat_vector<T> &a,
                       const flat_vector<T> &b) noexcept {
    return a.len() < b.len();
}
template <Number T>
std::istream &operator>>(std::istream &in, flat_vector<T> &f) {
    in >> f.x >> f.y;
    return in;
}
template <Number T>
std::ostream &operator<<(std::ostream &out, const flat_vector<T> &f) {
    out << '{' << f.x << ", " << f.y << '}';
    return out;
}
template <Number T> bool eq_zero(T d, double eps) noexcept {
    d = (d < 0 ? -d : d);
    return d < eps;
}
template <Number T>
flat_vector<T> intersection(const flat_vector<T> &a, const flat_vector<T> &b,
                            const flat_vector<T> &c, const flat_vector<T> &d) {
    if (a == b && b == c && c == d) {
        return a;
    }
    T n;
    if (!eq_zero(b.y - a.y)) {
        T q = (b.x - a.x) / (a.y - b.y);
        T sn = (c.x - d.x) + (c.y - d.y) * q;
        if (eq_zero(sn)) {
            throw std::logic_error("Lines do not cross");
        }
        T fn = (c.x - a.x) + (c.y - a.y) * q;
        n = fn / sn;
    } else {
        if (eq_zero(c.y - d.y)) {
            throw std::logic_error("Lines do not cross");
        }
        n = (c.y - a.y) / (c.y - d.y);
    }
    T x = c.x + (d.x - c.x) * n;
    T y = c.y + (d.y - c.y) * n;
    return flat_vector<T>(x, y);
}