// #include "pentagon.hpp"

// Pentagon::Pentagon() : Polygonal() {}

// Pentagon::Pentagon(const std::initializer_list<flat_vector> &list)
//     : Polygonal(list) {
//     validatePointsCount(points.size());
// }

// Pentagon::Pentagon(const std::vector<flat_vector> &vect) : Polygonal(vect) {
//     validatePointsCount(points.size());
// }

// Pentagon::Pentagon(const Pentagon &other) : Polygonal(other) {}

// Pentagon::Pentagon(Pentagon &&other) noexcept : Polygonal(std::move(other))
// {}

// Pentagon &Pentagon::operator=(const Pentagon &other) {
//     if (this != &other) {
//         Polygonal::operator=(other);
//     }
//     return *this;
// }

// Pentagon &Pentagon::operator=(Pentagon &&other) noexcept {
//     if (this != &other) {
//         Polygonal::operator=(std::move(other));
//     }
//     return *this;
// }

// void Pentagon::validatePointsCount(size_t count) const {
//     if (count != 5) {
//         throw std::logic_error("Error: A Pentagon must have exactly 5
//         points.");
//     }
// }