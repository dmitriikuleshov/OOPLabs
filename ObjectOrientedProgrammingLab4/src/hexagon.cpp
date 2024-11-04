// #include "hexagon.hpp"

// Hexagon::Hexagon() : Polygonal() {}

// Hexagon::Hexagon(const std::initializer_list<flat_vector> &list)
//     : Polygonal(list) {
//     validatePointsCount(points.size());
// }

// Hexagon::Hexagon(const std::vector<flat_vector> &vect) : Polygonal(vect) {
//     validatePointsCount(points.size());
// }

// Hexagon::Hexagon(const Hexagon &other) : Polygonal(other) {}

// Hexagon::Hexagon(Hexagon &&other) noexcept : Polygonal(std::move(other)) {}

// Hexagon &Hexagon::operator=(const Hexagon &other) {
//     if (this != &other) {
//         Polygonal::operator=(other);
//     }
//     return *this;
// }

// Hexagon &Hexagon::operator=(Hexagon &&other) noexcept {
//     if (this != &other) {
//         Polygonal::operator=(std::move(other));
//     }
//     return *this;
// }

// void Hexagon::validatePointsCount(size_t count) const {
//     if (count != 6) {
//         throw std::logic_error("Error: A Hexagon must have exactly 6
//         points.");
//     }
// }