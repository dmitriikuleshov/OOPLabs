#pragma once
#include "npc.hpp"
#include "visitor.hpp"

class Knight : public NPC {
  protected:
    Knight(const std::string &name, int x, int y)
        : NPC(KnightType, 'K', name, x, y) {}

  public:
    static std::shared_ptr<NPC> create(const std::string &name, int x, int y) {
        return std::const_pointer_cast<NPC>(
            std::make_shared<Knight>(name, x, y));
    }

    void print() override { std::cout << *this; }

    void accept(AttackerVisitor &visitor) override {
        visitor.visit(shared_from_this());
    }

    void save(std::ostream &os) override {
        os << KnightType << std::endl;
        NPC::save(os);
    }
    friend std::ostream &operator<<(std::ostream &os, Knight &Knight) {
        os << "Knight: " << *static_cast<NPC *>(&Knight) << std::endl;
        return os;
    }
};
