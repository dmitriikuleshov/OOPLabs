#include "list_memory_resource.hpp"
#include "pmr_queue.hpp"
#include <iostream>
#include <memory_resource>
#include <string>

struct ComplexType {
    int id;
    std::string name;
    double value;

    ComplexType(int id, const std::string &name, double value)
        : id(id), name(name), value(value) {}
};

int main() {
    ListMemoryResource memory_resource;

    // Queue with int
    PmrQueue<int> intQueue(&memory_resource);
    intQueue.push(1);
    intQueue.push(2);
    intQueue.push(3);

    std::cout << "Integer Queue: ";
    for (auto it = intQueue.begin(); it != intQueue.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Queue with ComplexType
    PmrQueue<ComplexType> complexQueue(&memory_resource);
    complexQueue.push(ComplexType(1, "Item1", 10.5));
    complexQueue.push(ComplexType(2, "Item2", 20.75));

    std::cout << "ComplexType Queue:\n";
    for (auto it = complexQueue.begin(); it != complexQueue.end(); ++it) {
        std::cout << "ID: " << it->id << ", Name: " << it->name
                  << ", Value: " << it->value << "\n";
    }

    return 0;
}
