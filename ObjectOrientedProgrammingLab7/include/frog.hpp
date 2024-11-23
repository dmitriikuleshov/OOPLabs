#pragma once
#include "npc.hpp"
#include "visitor.hpp"

class Frog : public NPC {
  protected:
    Frog(const std::string &name, int x, int y)
        : NPC(FrogType, 'F', name, x, y) {}

  public:
    static std::shared_ptr<NPC> create(const std::string &name, int x, int y) {
        return std::const_pointer_cast<NPC>(std::make_shared<Frog>(name, x, y));
    }

    void print() override { std::cout << *this; }

    void accept(AttackerVisitor &visitor) override {
        visitor.visit(shared_from_this());
    }

    void save(std::ostream &os) override {
        os << FrogType << std::endl;
        NPC::save(os);
    }
    friend std::ostream &operator<<(std::ostream &os, Frog &Frog) {
        os << "Knight: " << *static_cast<NPC *>(&Frog) << std::endl;
        return os;
    }
};
