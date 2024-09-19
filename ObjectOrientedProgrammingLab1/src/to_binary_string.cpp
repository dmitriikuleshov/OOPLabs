
#include "to_binary_string.h"

std::string to_binary_string(uint32_t n) {
    std::bitset<32> binary(n);
    return binary.to_string();
}
