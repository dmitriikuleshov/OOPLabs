
#include "to_binary_string.h"

std::string to_binary_string(uint32_t n) {
    // std::bitset < 32> binary(n);
    // std::string result = binary.to_string();
    std::string result = "";
    for (size_t i = 0; i < 32; ++i) {
        result = std::to_string(n % 2) + result;
        n /= 2;
    }
    return result;
}
