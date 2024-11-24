#ifndef FROG_HPP
#define FROG_HPP

#include "npc.hpp"

class Frog : public NPC {

  public:
    Frog(const std::string &name, int x, int y);
    static ptr<NPC> create(const std::string &name, int x, int y);
    void print() override;
    void accept(AttackerVisitor &visitor) override;
    void save(std::ostream &os) override;
    friend std::ostream &operator<<(std::ostream &os, Frog &Frog);
};

#endif // FROG_HPP
