#include "dragon.hpp"

Dragon::Dragon(const std::string &name, int x, int y)
    : NPC(DragonType, name, x, y) {}
Dragon::Dragon(std::istream &is) : NPC(DragonType, is) {}

void Dragon::accept(AttackerVisitor &visitor) {
    visitor.visit(shared_from_this());
}

void Dragon::print() { std::cout << *this; }

void Dragon::save(std::ostream &os) {
    os << DragonType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Dragon &dragon) {
    os << "Dragon: " << *static_cast<NPC *>(&dragon) << std::endl;
    return os;
}