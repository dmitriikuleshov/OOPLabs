#ifndef KNITHT_HPP
#define KNIGHT_HPP

#include "npc.hpp"

class Knight : public NPC {
  public:
    Knight(const std::string &name, int x, int y);
    static ptr<NPC> create(const std::string &name, int x, int y);
    void print() override;
    void accept(ptr<AttackerVisitor> &visitor) override;
    void save(std::ostream &os) override;
    friend std::ostream &operator<<(std::ostream &os, Knight &Knight);
};

#endif // KNIGHT_HPP