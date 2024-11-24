#ifndef OBSERVERS_HPP
#define OBSERVERS_HPP

#include "npc.hpp"

class TextObserver final : public IFightObserver {
  private:
    TextObserver() {};

  public:
    static ptr<IFightObserver> get() {
        static TextObserver instance;
        return ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const ptr<NPC> attacker, const ptr<NPC> defender,
                  bool win) override {
        if (win) {
            std::cout << std::endl << "Murder --------" << std::endl;
            std::cout << "killer: ";
            attacker->print();
            std::cout << "victim: ";
            defender->print();
        }
    }
};

class FileObserver final : public IFightObserver {
  private:
    FileObserver() {};

  public:
    static ptr<IFightObserver> get() {
        static FileObserver instance;
        return ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const ptr<NPC> attacker, const ptr<NPC> defender,
                  bool win) override {
        if (win) {
            std::ofstream fs("log.txt", std::ios::app);
            fs << std::endl
               << "Murder --------" << std::endl
               << "killer: " << *attacker << std::endl
               << "victim: " << *defender;
            fs.close();
        }
    }
};

#endif // OBSERVERS_HPP