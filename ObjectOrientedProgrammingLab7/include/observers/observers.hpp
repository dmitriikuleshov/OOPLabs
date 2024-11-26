#ifndef OBSERVERS_HPP
#define OBSERVERS_HPP

#include "npc.hpp"

struct FightObserver {
    virtual void on_fight(const ptr<NPC> attacker, const ptr<NPC> defender) = 0;
};

class TextObserver final : public FightObserver {
  private:
    TextObserver();

  public:
    static ptr<FightObserver> get();
    void on_fight(const ptr<NPC> attacker, const ptr<NPC> defender) override;
};

class FileObserver final : public FightObserver {
  private:
    FileObserver();

  public:
    static ptr<FightObserver> get();
    void on_fight(const ptr<NPC> attacker, const ptr<NPC> defender) override;
};

#endif // OBSERVERS_HPP