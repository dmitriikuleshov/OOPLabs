#include "knight.hpp"

Knight::Knight(const std::string &name, int x, int y)
    : NPC(KnightType, 'K', name, x, y) {}

ptr<NPC> Knight::create(const std::string &name, int x, int y) {
    return std::static_pointer_cast<NPC>(std::make_shared<Knight>(name, x, y));
}

void Knight::print() { std::cout << *this; }

void Knight::accept(ptr<AttackerVisitor> &visitor) {
    visitor->visit(shared_from_this());
}

void Knight::save(std::ostream &os) {
    os << KnightType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Knight &Knight) {
    os << "Knight: " << *static_cast<NPC *>(&Knight) << std::endl;
    return os;
}