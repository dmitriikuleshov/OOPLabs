#pragma once
#include "factory.hpp"
#include "npc.hpp"

void save(const set_t &array, const std::string &filename);

set_t load_field(const std::string &filename);

set_t fight(const set_t &array, size_t distance);

std::ostream &operator<<(std::ostream &os, const set_t &array);