#include "array.hpp"
#include "twelve.hpp"
#include "twelve_digit.hpp"
#include <iostream>
#include <string>

int main() {
    Twelve num1("108");
    Twelve num2("108");
    std::cout << "NUM1: " << num1 << std::endl;
    num1 += num2;
    std::cout << num1 << std::endl;
    return 0;
}