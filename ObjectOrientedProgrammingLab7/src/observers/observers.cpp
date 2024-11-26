#include "observers.hpp"

// TextObserver

TextObserver::TextObserver() {}

ptr<FightObserver> TextObserver::get() {
    static TextObserver instance;
    return ptr<FightObserver>(&instance, [](FightObserver *) {});
}

void TextObserver::on_fight(const ptr<NPC> attacker, const ptr<NPC> defender) {
    std::cout << std::endl << "Murder --------" << std::endl;
    std::cout << "killer: ";
    attacker->print();
    std::cout << "victim: ";
    defender->print();
    std::cout << '\n';
}

// FileObserver

FileObserver::FileObserver() {}

ptr<FightObserver> FileObserver::get() {
    static FileObserver instance;
    return ptr<FightObserver>(&instance, [](FightObserver *) {});
}

void FileObserver::on_fight(const ptr<NPC> attacker, const ptr<NPC> defender) {
    std::ofstream fs("log.txt", std::ios::app);
    fs << '\n'
       << "Murder --------" << '\n'
       << "killer: " << *attacker << '\n'
       << "victim: " << *defender << '\n';
    fs.close();
}