#pragma once
#include "npc.hpp"
#include "visitor.hpp"

class Dragon : public NPC {
  protected:
    Dragon(const std::string &name, int x, int y)
        : NPC(DragonType, name, x, y) {}
    Dragon(std::istream &is) : NPC(DragonType, is) {}

  public:
    static std::shared_ptr<NPC> create(const std::string &name, int x, int y) {
        return std::const_pointer_cast<NPC>(
            std::make_shared<Dragon>(name, x, y));
    }

    void print() override { std::cout << *this; }

    void accept(AttackerVisitor &visitor) override {
        visitor.visit(shared_from_this());
    }

    void save(std::ostream &os) override {
        os << DragonType << std::endl;
        NPC::save(os);
    }
    friend std::ostream &operator<<(std::ostream &os, Dragon &Dragon) {
        os << "Dragon: " << *static_cast<NPC *>(&Dragon) << std::endl;
        return os;
    }
};
