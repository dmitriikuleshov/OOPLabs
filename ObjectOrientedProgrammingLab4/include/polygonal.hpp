#pragma once

#include "figure.hpp"
#include "flat_vector.hpp"
#include <algorithm>
#include <cmath>

#include <list>
#include <vector>

// --------------- HEADER ---------------

const int COLLINEAR = 0;
const int CLOCKWISE = 1;
const int COUNTER_CLOCKWISE = 2;

template <Number T>
int orientation(flat_vector<T> p, flat_vector<T> q, flat_vector<T> r);

template <Number T> class Polygonal : public Figure<T> {
  public:
    std::vector<flat_vector<T>> points;

    // Constructors

    Polygonal();

    Polygonal(const std::initializer_list<flat_vector<T>> &list);

    Polygonal(const std::vector<flat_vector<T>> &vect);

    Polygonal(const Polygonal &other);

    Polygonal(Polygonal &&other) noexcept;

    // Copy Assignment Operator

    Polygonal &operator=(const Polygonal &other);

    // Move Assignment Operator

    Polygonal &operator=(Polygonal &&other) noexcept;

    // Comparison

    bool operator==(const Polygonal &other) const noexcept;

    // Calculation functions

    virtual flat_vector<T> centroid() const override;

    virtual T area() const noexcept override;

    virtual operator double() const noexcept override;

    virtual ~Polygonal() = default;

  private:
    void jarvisMatch();

    void removeDuplicatePoints();

    bool allPointsAreOnTheSameLine();

  protected:
    // Stream operators

    virtual std::istream &read_from_stream(std::istream &in) override;

    virtual std::ostream &print_in_stream(std::ostream &out) const override;
};

// --------------- IMPLEMENTATION ---------------

template <Number T>
int orientation(const flat_vector<T> p, const flat_vector<T> q,
                const flat_vector<T> r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return COLLINEAR;
    return (val > 0) ? CLOCKWISE : COUNTER_CLOCKWISE;
}

// Constructors

template <Number T> Polygonal<T>::Polygonal() {}

template <Number T>
Polygonal<T>::Polygonal(const std::initializer_list<flat_vector<T>> &list) {

    points = list;
    removeDuplicatePoints();

    if (points.size() < 3) {
        throw std::invalid_argument(
            "Error: Polygonal(std::initializer_list<flat_vector>&) takes at "
            "least 3 points in flat_vector!\n");
    }

    if (allPointsAreOnTheSameLine()) {
        throw std::logic_error(
            "Error: all points of Polygonal on the same line!");
    }

    jarvisMatch();
}

template <Number T>
Polygonal<T>::Polygonal(const std::vector<flat_vector<T>> &vect) {
    points = vect;
    removeDuplicatePoints();

    if (points.size() < 3) {
        throw std::invalid_argument(
            "Error: Polygonal(std::initializer_list<flat_vector>&) takes at "
            "least 3 points in flat_vector!\n");
    }

    if (allPointsAreOnTheSameLine()) {
        throw std::logic_error(
            "Error: all points of Polygonal on the same line!");
    }
    jarvisMatch();
}

template <Number T> bool Polygonal<T>::allPointsAreOnTheSameLine() {
    bool on_the_same_line = true;
    for (flat_vector p : points) {
        if ((points[1].x - points[0].x == 0 ||
             points[1].y - points[0].y == 0) ||
            (p.x - points[0].x) * (points[1].y - points[0].y) !=
                (p.y - points[0].y) * (points[1].x - points[0].x)) {
            on_the_same_line = false;
            break;
        }
    }
    return on_the_same_line;
}

template <Number T> void Polygonal<T>::removeDuplicatePoints() {
    std::sort(points.begin(), points.end(), cmp_by_len<T>);
    auto last = std::unique(points.begin(), points.end());
    points.erase(last, points.end());
}

template <Number T> void Polygonal<T>::jarvisMatch() {
    int size = points.size();
    if (size < 3) {
        throw std::logic_error("Error: There are not enough points to build a "
                               "convex hull. Need at least 3 points!\n");
    }
    std::vector<flat_vector<T>> hull;
    int left_most = 0;
    for (int i = 1; i < size; ++i) {
        if (points[i].x < points[left_most].x) {
            left_most = i;
        }
    }

    int p = left_most, q;
    do {
        hull.push_back(points[p]);
        q = (p + 1) % size;

        for (int i = 0; i < size; ++i) {
            if (orientation(points[p], points[i], points[q]) ==
                COUNTER_CLOCKWISE) {
                q = i;
            }
        }
        p = q;
    } while (p != left_most);
    if (hull.size() < 3) {
        throw std::logic_error("Error: There are not enough points to build a "
                               "convex hull. Need at least three points that "
                               "do not lie on the same straight line!\n");
    }
    points = hull;
}

// Copy Constructor
template <Number T>
Polygonal<T>::Polygonal(const Polygonal &other) : points(other.points) {}

// Move Constructor
template <Number T>
Polygonal<T>::Polygonal(Polygonal &&other) noexcept
    : points(std::move(other.points)) {}

// Copy Assignment Operator
template <Number T>
Polygonal<T> &Polygonal<T>::operator=(const Polygonal &other) {
    if (this == &other) {
        return *this;
    }
    points = other.points;
    return *this;
}

// Move Assignment Operator
template <Number T>
Polygonal<T> &Polygonal<T>::operator=(Polygonal &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    points = std::move(other.points);
    return *this;
}

// Comparison
template <Number T>
bool Polygonal<T>::operator==(const Polygonal &other) const noexcept {
    int size = points.size();
    if (size != other.points.size()) {
        return false;
    }

    int shift;
    while (points[0] != other.points[shift]) {
        ++shift;
        if (shift >= size) {
            return false;
        }
    }

    try {
        for (size_t i = 0; i < size; ++i) {
            if (points[i] != other.points[(i + shift) % size]) {
                return false;
            }
        }
    } catch (...) {
        return false;
    }

    return true;
}

// Calculation functions
template <Number T> flat_vector<T> Polygonal<T>::centroid() const {
    // flat_vector triangle_centroid_point;
    // flat_vector result;

    // for (size_t i = 2; i < points.size(); ++i) {
    //     Polygonal triangle = {points[0], points[i], points[i - 1]};

    //     triangle_centroid_point =
    //         (points[0] + points[i] + points[i - 1]) * (1.0 / 3.0);
    //     result += triangle_centroid_point * triangle.area();
    // }

    // return result * (1.0 / area());

    flat_vector<T> result(T(0.0), T(0.0));
    for (size_t i = 0; i < points.size(); ++i) {
        result += points[i];
    }
    result *= (1.0 / (double)points.size());
    return result;
}

template <Number T> T Polygonal<T>::area() const noexcept {
    std::vector<flat_vector<T>> diagonals;
    for (size_t i = 1; i < points.size(); ++i) {
        diagonals.push_back(points[i] - points[0]);
    }

    T triangle_area_sum = 0.0;
    for (size_t i = 1; i < diagonals.size(); ++i) {
        triangle_area_sum += triangle_area(diagonals[i], diagonals[i - 1]);
    }

    return triangle_area_sum;
}

template <Number T> Polygonal<T>::operator double() const noexcept {
    return area();
}

// Stream operators
template <Number T>
std::istream &Polygonal<T>::read_from_stream(std::istream &in) {
    flat_vector<T> point;
    while (in >> point) {
        points.push_back(point);
    }
    return in;
}

template <Number T>
std::ostream &Polygonal<T>::print_in_stream(std::ostream &out) const {
    out << '(';
    for (const auto point : points) {
        out << point << " ";
    }
    out << ')';
    return out;
}
