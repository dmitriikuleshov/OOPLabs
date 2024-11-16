#include "array.hpp"
#include "flat_vector.hpp"
#include "polygonal.hpp"
#include <iostream>
#include <memory>

int main() {
    auto p1 = std::make_shared<Polygonal<double>>(
        Polygonal<double>{{0, 0}, {1, 1}, {0, 2}});
    auto p2 = std::make_shared<Polygonal<double>>(
        Polygonal<double>{{0, 0}, {4, 0}, {4, 3}, {0, 3}});
    auto p3 = std::make_shared<Polygonal<double>>(
        Polygonal<double>{{1, 1}, {3, 1}, {4, 3}, {2, 5}, {0, 3}});

    auto arr = Array<std::shared_ptr<Figure<double>>>();
    arr.push_back(p1);
    arr.push_back(p2);
    arr.push_back(p3);

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << *arr[i] << std::endl;
    }

    std::cout << "Erasing second element" << std::endl;
    arr.erase(1);

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << *arr[i] << std::endl;
    }

    std::cout << "Inserting second element back" << std::endl;
    arr.insert(1, p2);

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << *arr[i] << std::endl;
    }

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i]->area() << std::endl;
    }

    Polygonal<int> p4{{1, 1}, {3, 1}, {4, 3}, {2, 5}, {0, 20}};
    Polygonal<double> p5{{1, 1}, {3, 1}, {4, 3}, {2, 5}, {0, 20}};
    std::cout << "int {1, 1}, {3, 1}, {4, 3}, {2, 5}, {0, 20} polygonal area: "
              << p4.area() << std::endl;
    std::cout
        << "double {1, 1}, {3, 1}, {4, 3}, {2, 5}, {0, 20} polygonal area: "
        << p5.area() << std::endl;

    return 0;
}
