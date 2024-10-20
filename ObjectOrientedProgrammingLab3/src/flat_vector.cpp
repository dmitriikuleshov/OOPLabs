#include "flat_vector.hpp"

bool areAlmostEqual(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}

flat_vector::flat_vector() noexcept : x{0}, y{0} {}

flat_vector::flat_vector(double x, double y) noexcept : x(x), y(y) {}

flat_vector flat_vector::operator+(const flat_vector &other) const noexcept {
    flat_vector tmp = *this;
    return tmp += other;
}

flat_vector &flat_vector::operator+=(const flat_vector &other) noexcept {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

flat_vector flat_vector::operator-(const flat_vector &other) const noexcept {
    flat_vector tmp = *this;
    return tmp -= other;
}

flat_vector &flat_vector::operator-=(const flat_vector &other) noexcept {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

flat_vector flat_vector::operator-() const noexcept {
    flat_vector tmp = *this;
    return ~tmp;
}

flat_vector flat_vector::operator*(const double &lambda) const noexcept {
    flat_vector tmp = *this;
    return tmp *= lambda;
}

flat_vector operator*(double lambda, const flat_vector &v) noexcept {
    return v * lambda;
}

flat_vector &flat_vector::operator*=(const double &lambda) noexcept {
    this->x *= lambda;
    this->y *= lambda;
    return *this;
}

double flat_vector::dot(const flat_vector &other) const noexcept {
    return (this->x * other.x) + (this->y * other.y);
}

double flat_vector::len() const noexcept { return sqrt(this->dot(*this)); }

double flat_vector::polar_angle() const noexcept {
    if (x == 0 && y == 0) {
        return 0.0;
    } else {
        return atan2(y, x);
    }
}

flat_vector &operator~(flat_vector &v) noexcept {
    v.x = -v.x;
    v.y = -v.y;
    return v;
}

bool flat_vector::operator==(const flat_vector &other) const noexcept {
    return areAlmostEqual(this->x, other.x) && areAlmostEqual(this->y, other.y);
}

bool flat_vector::operator!=(const flat_vector &other) const noexcept {
    return !(*this == other);
}

double triangle_area(const flat_vector &a, const flat_vector &b) noexcept {
    return abs(((a.x * b.y) - (a.y * b.x))) / 2.0;
}

double angle(const flat_vector &a, const flat_vector &b) noexcept {
    double scalar = a.dot(b);
    if (scalar == 0) {
        return M_PI / 2;
    } else {
        return atan2(2.0 * triangle_area(a, b), scalar);
    }
}

bool cmp_by_polar_angle(const flat_vector &a, const flat_vector &b) noexcept {
    return a.polar_angle() < b.polar_angle();
}

bool cmp_by_len(const flat_vector &a, const flat_vector &b) noexcept {
    return a.len() < b.len();
}

std::istream &operator>>(std::istream &in, flat_vector &f) {
    in >> f.x >> f.y;
    return in;
}

std::ostream &operator<<(std::ostream &out, const flat_vector &f) {
    out << '{' << f.x << ", " << f.y << '}';
    return out;
}

bool double_eq_zero(double d, double eps) noexcept {
    d = (d < 0 ? -d : d);
    return d < eps;
}

flat_vector intersection(const flat_vector &a, const flat_vector &b,
                         const flat_vector &c, const flat_vector &d) {
    if (a == b && b == c && c == d) {
        return a;
    }
    double n;
    if (!double_eq_zero(b.y - a.y)) {
        double q = (b.x - a.x) / (a.y - b.y);
        double sn = (c.x - d.x) + (c.y - d.y) * q;
        if (double_eq_zero(sn)) {
            throw std::logic_error("Lines do not cross");
        }
        double fn = (c.x - a.x) + (c.y - a.y) * q;
        n = fn / sn;
    } else {
        if (double_eq_zero(c.y - d.y)) {
            throw std::logic_error("Lines do not cross");
        }
        n = (c.y - a.y) / (c.y - d.y);
    }
    double x = c.x + (d.x - c.x) * n;
    double y = c.y + (d.y - c.y) * n;
    return flat_vector(x, y);
}