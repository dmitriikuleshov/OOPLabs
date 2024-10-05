#include "array.hpp"
#include <iostream>

int main() {
    Array<int> arr;
    arr.push_back(1);
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << std::endl;
    }
    return 0;
}