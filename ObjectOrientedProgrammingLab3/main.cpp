// Var 6
#include "array.hpp"
#include "flat_vector.hpp"
#include "polygonal.hpp"

int main() {
    Polygonal p1{{0, 0}, {1, 1}, {0, 2}};
    Polygonal p2{{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    Polygonal p3{{1, 1}, {3, 1}, {4, 3}, {2, 5}, {0, 3}};
    Array<Polygonal *> arr;
    arr.push_back(&p1);
    arr.push_back(&p2);
    arr.push_back(&p3);

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << *arr[i] << std::endl;
    }

    std::cout << "Erasing second element" << std::endl;
    arr.erase(1);

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << *arr[i] << std::endl;
    }

    std::cout << "Inserting second element back" << std::endl;
    arr.insert(1, &p2);

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << *arr[i] << std::endl;
    }

    return 0;
}