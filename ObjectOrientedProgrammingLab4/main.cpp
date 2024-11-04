// Var 6
#include "array.hpp"
#include "flat_vector.hpp"
#include "polygonal.hpp"

int main() {
    Polygonal<double> p1{{0, 0}, {1, 1}, {0, 2}};
    Polygonal<double> p2{{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    Polygonal<double> p3{{1, 1}, {3, 1}, {4, 3}, {2, 5}, {0, 3}};
    Array<Polygonal<double> *> arr;
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

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << (*arr[i]).area() << std::endl;
    }

    return 0;
}