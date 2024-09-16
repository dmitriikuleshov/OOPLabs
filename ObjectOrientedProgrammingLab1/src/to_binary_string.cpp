#include <bitset>
#include <iostream>

std::string to_binary_string(uint32_t n) {
    std::bitset<32> binary(n);
    return binary.to_string();
}
