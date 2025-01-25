#ifndef DRAGON_HPP
#define DRAGON_HPP

#include "npc.hpp"

class Dragon : public NPC {
  public:
    Dragon(const std::string &name, int x, int y);
    static ptr<NPC> create(const std::string &name, int x, int y);
    void print() override;
    void accept(ptr<AttackerVisitor> &visitor);
    void save(std::ostream &os) override;
    friend std::ostream &operator<<(std::ostream &os, Dragon &Dragon);
};

#endif // DRAGON_HPP