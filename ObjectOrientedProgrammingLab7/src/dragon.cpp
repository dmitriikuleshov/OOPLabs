#include "dragon.hpp"

Dragon::Dragon(const std::string &name, int x, int y)
    : NPC(DragonType, 'D', name, x, y) {}

ptr<NPC> Dragon::create(const std::string &name, int x, int y) {
    return std::static_pointer_cast<NPC>(std::make_shared<Dragon>(name, x, y));
}

void Dragon::print() { std::cout << *this; }

void Dragon::accept(AttackerVisitor &visitor) {
    visitor.visit(shared_from_this());
}

void Dragon::save(std::ostream &os) {
    os << DragonType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Dragon &Dragon) {
    os << "Dragon: " << *static_cast<NPC *>(&Dragon) << std::endl;
    return os;
}