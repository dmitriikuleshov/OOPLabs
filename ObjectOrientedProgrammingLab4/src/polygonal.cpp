// #include <algorithm>
// #include <exception>

// #include "polygonal.hpp"

// int orientation(const flat_vector p, const flat_vector q, const flat_vector
// r) {
//     int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

//     if (val == 0)
//         return COLLINEAR;
//     return (val > 0) ? CLOCKWISE : COUNTER_CLOCKWISE;
// }

// // Constructors
// Polygonal::Polygonal() {}

// Polygonal::Polygonal(const std::initializer_list<flat_vector> &list) {
//     points = list;
//     removeDuplicatePoints();

//     if (points.size() < 3) {
//         throw std::invalid_argument(
//             "Error: Polygonal(std::initializer_list<flat_vector>&) takes at "
//             "least 3 points in flat_vector!\n");
//     }

//     if (allPointsAreOnTheSameLine()) {
//         throw std::logic_error(
//             "Error: all points of Polygonal on the same line!");
//     }
//     jarvisMatch();
// }

// Polygonal::Polygonal(const std::vector<flat_vector> &vect) {
//     points = vect;
//     removeDuplicatePoints();

//     if (points.size() < 3) {
//         throw std::invalid_argument(
//             "Error: Polygonal(std::initializer_list<flat_vector>&) takes at "
//             "least 3 points in flat_vector!\n");
//     }

//     if (allPointsAreOnTheSameLine()) {
//         throw std::logic_error(
//             "Error: all points of Polygonal on the same line!");
//     }
//     jarvisMatch();
// }

// bool Polygonal::allPointsAreOnTheSameLine() {
//     bool on_the_same_line = true;
//     for (flat_vector p : points) {
//         if ((p.x - points[0].x) / (points[1].x - points[0].x) !=
//             (p.y - points[0].y) / (points[1].y - points[0].y)) {
//             on_the_same_line = false;
//             break;
//         }
//     }
//     return on_the_same_line;
// }

// void Polygonal::removeDuplicatePoints() {
//     std::sort(points.begin(), points.end(), cmp_by_len);
//     auto last = std::unique(points.begin(), points.end());
//     points.erase(last, points.end());
// }

// void Polygonal::jarvisMatch() {
//     int size = points.size();
//     if (size < 3) {
//         throw std::logic_error("Error: There are not enough points to build a
//         "
//                                "convex hull. Need at least 3 points!\n");
//     }
//     std::vector<flat_vector> hull;
//     int left_most = 0;
//     for (int i = 1; i < size; ++i) {
//         if (points[i].x < points[left_most].x) {
//             left_most = i;
//         }
//     }

//     int p = left_most, q;
//     do {
//         hull.push_back(points[p]);
//         q = (p + 1) % size;

//         for (int i = 0; i < size; ++i) {
//             if (orientation(points[p], points[i], points[q]) ==
//                 COUNTER_CLOCKWISE) {
//                 q = i;
//             }
//         }
//         p = q;
//     } while (p != left_most);
//     if (hull.size() < 3) {
//         throw std::logic_error("Error: There are not enough points to build a
//         "
//                                "convex hull. Need at least three points that
//                                " "do not lie on the same straight line!\n");
//     }
//     points = hull;
// }

// // Copy Constructor
// Polygonal::Polygonal(const Polygonal &other) : points(other.points) {}

// // Move Constructor
// Polygonal::Polygonal(Polygonal &&other) noexcept
//     : points(std::move(other.points)) {}

// // Copy Assignment Operator
// Polygonal &Polygonal::operator=(const Polygonal &other) {
//     if (this == &other) {
//         return *this;
//     }
//     points = other.points;
//     return *this;
// }

// // Move Assignment Operator
// Polygonal &Polygonal::operator=(Polygonal &&other) noexcept {
//     if (this == &other) {
//         return *this;
//     }
//     points = std::move(other.points);
//     return *this;
// }

// // Comparison
// bool Polygonal::operator==(const Polygonal &other) const noexcept {
//     int size = points.size();
//     if (size != other.points.size()) {
//         return false;
//     }

//     int shift;
//     while (points[0] != other.points[shift]) {
//         ++shift;
//         if (shift >= size) {
//             return false;
//         }
//     }

//     try {
//         for (size_t i = 0; i < size; ++i) {
//             if (points[i] != other.points[(i + shift) % size]) {
//                 return false;
//             }
//         }
//     } catch (...) {
//         return false;
//     }

//     return true;
// }

// // Calculation functions
// flat_vector Polygonal::centroid() const {
//     // flat_vector triangle_centroid_point;
//     // flat_vector result;

//     // for (size_t i = 2; i < points.size(); ++i) {
//     //     Polygonal triangle = {points[0], points[i], points[i - 1]};

//     //     triangle_centroid_point =
//     //         (points[0] + points[i] + points[i - 1]) * (1.0 / 3.0);
//     //     result += triangle_centroid_point * triangle.area();
//     // }

//     // return result * (1.0 / area());

//     flat_vector result(0.0, 0.0);
//     for (size_t i = 0; i < points.size(); ++i) {
//         result += points[i];
//     }
//     result *= (1.0 / (double)points.size());
//     return result;
// }

// double Polygonal::area() const noexcept {
//     std::vector<flat_vector> diagonals;
//     for (size_t i = 1; i < points.size(); ++i) {
//         diagonals.push_back(points[i] - points[0]);
//     }

//     double triangle_area_sum = 0.0;
//     for (size_t i = 1; i < diagonals.size(); ++i) {
//         triangle_area_sum += triangle_area(diagonals[i], diagonals[i - 1]);
//     }

//     return triangle_area_sum;
// }

// Polygonal::operator double() const noexcept { return area(); }

// // Stream operators
// std::istream &Polygonal::read_from_stream(std::istream &in) {
//     flat_vector point;
//     while (in >> point) {
//         points.push_back(point);
//     }
//     return in;
// }

// std::ostream &Polygonal::print_in_stream(std::ostream &out) const {
//     out << '(';
//     for (const auto point : points) {
//         out << point << " ";
//     }
//     out << ')';
//     return out;
// }
