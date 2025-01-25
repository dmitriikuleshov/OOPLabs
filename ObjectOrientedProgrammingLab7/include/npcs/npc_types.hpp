#ifndef NPC_TYPES_HPP
#define NPC_TYPES_HPP

#include <memory>
#include <string>
#include <unordered_map>

class NPC;

template <class T> using ptr = std::shared_ptr<T>;

enum NpcType { UnknownType = 0, DragonType = 1, KnightType = 2, FrogType = 3 };

const std::unordered_map<std::string, NpcType> StringToNpcType = {
    {"Unknown", NpcType::UnknownType},
    {"Dragon", NpcType::DragonType},
    {"Knight", NpcType::KnightType},
    {"Frog", NpcType::FrogType}};

#endif // NPC_TYPES_HPP