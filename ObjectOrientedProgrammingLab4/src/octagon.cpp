// #include "octagon.hpp"

// Octagon::Octagon() : Polygonal() {}

// Octagon::Octagon(const std::initializer_list<flat_vector> &list)
//     : Polygonal(list) {
//     validatePointsCount(points.size());
// }

// Octagon::Octagon(const std::vector<flat_vector> &vect) : Polygonal(vect) {
//     validatePointsCount(points.size());
// }

// Octagon::Octagon(const Octagon &other) : Polygonal(other) {}

// Octagon::Octagon(Octagon &&other) noexcept : Polygonal(std::move(other)) {}

// Octagon &Octagon::operator=(const Octagon &other) {
//     if (this != &other) {
//         Polygonal::operator=(other);
//     }
//     return *this;
// }

// Octagon &Octagon::operator=(Octagon &&other) noexcept {
//     if (this != &other) {
//         Polygonal::operator=(std::move(other));
//     }
//     return *this;
// }

// void Octagon::validatePointsCount(size_t count) const {
//     if (count != 8) {
//         throw std::logic_error("Error: A Octagon must have exactly 8
//         points.");
//     }
// }