#include "knight.hpp"

Knight::Knight(const std::string &name, int x, int y)
    : NPC(KnightType, name, x, y) {}
Knight::Knight(std::istream &is) : NPC(KnightType, is) {}

void Knight::accept(AttackerVisitor &visitor) {
    visitor.visit(shared_from_this());
}

void Knight::print() { std::cout << *this; }

void Knight::save(std::ostream &os) {
    os << KnightType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Knight &Knight) {
    os << "Knight: " << *static_cast<NPC *>(&Knight) << std::endl;
    return os;
}