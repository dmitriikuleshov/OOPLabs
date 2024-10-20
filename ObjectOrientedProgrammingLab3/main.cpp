// Var 6
#include "flat_vector.hpp"
#include "polygonal.hpp"

int main() {
    flat_vector a(-1, -4), b(4, 1), c(4, 3), d(-4, 3);

    Polygonal p{a, b, c, d};
    for (auto point : p.points) {
        std::cout << point.x << "\t" << point.y << std::endl;
    }
    std::cout << p.area();
    return 0;
}