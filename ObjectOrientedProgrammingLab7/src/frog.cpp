#include "frog.hpp"
#include "visitor.hpp"

Frog::Frog(const std::string &name, int x, int y) : NPC(FrogType, name, x, y) {}
Frog::Frog(std::istream &is) : NPC(FrogType, is) {}

void Frog::accept(AttackerVisitor &visitor) {
    visitor.visit(shared_from_this());
}

void Frog::print() { std::cout << *this; }

void Frog::save(std::ostream &os) {
    os << FrogType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Frog &Frog) {
    os << "Frog: " << *static_cast<NPC *>(&Frog) << std::endl;
    return os;
}