#include "frog.hpp"

Frog::Frog(const std::string &name, int x, int y)
    : NPC(FrogType, 'F', name, x, y) {}

ptr<NPC> Frog::create(const std::string &name, int x, int y) {
    return std::static_pointer_cast<NPC>(std::make_shared<Frog>(name, x, y));
}

void Frog::print() { std::cout << *this; }

void Frog::accept(ptr<AttackerVisitor> &visitor) {
    visitor->visit(shared_from_this());
}

void Frog::save(std::ostream &os) {
    os << FrogType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Frog &Frog) {
    os << "Frog: " << *static_cast<NPC *>(&Frog) << std::endl;
    return os;
}