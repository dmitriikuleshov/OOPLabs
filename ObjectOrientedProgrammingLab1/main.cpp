#include "to_binary_string.h"
#include <iostream>

int main() {
    uint32_t value;
    std::cout << "enter value:";
    std::cin >> value;
    std::cout << "result: " << to_binary_string(value) << std::endl;

    return 0;
}