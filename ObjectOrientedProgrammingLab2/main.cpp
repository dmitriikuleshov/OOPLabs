#include "twelve.hpp"
#include <iostream>

int main() {
    Twelve num1(11);
    Twelve num2("B");
    std::cout << "Num1 = 11, base10" << "Num2 = B, base12" << std::endl;
    std::cout << "Equality: " << (num1 == num2) << std::endl;
    std::cout << "Sum: " << num1 + num2 << std::endl;
    return 0;
}