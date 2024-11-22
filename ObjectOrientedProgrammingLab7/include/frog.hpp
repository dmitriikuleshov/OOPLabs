#pragma once
#include "npc.hpp"
#include "visitor.hpp"

struct Frog : public NPC {
    Frog(const std::string &name, int x, int y);
    Frog(std::istream &is);

    void print() const override;

    virtual bool accept(const std::shared_ptr<NPC> &attacker) const override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Dragon &dragon);
};