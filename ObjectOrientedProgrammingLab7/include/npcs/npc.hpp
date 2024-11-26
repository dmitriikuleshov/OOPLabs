#ifndef NPC_HPP
#define NPC_HPP

#include "attacker_visitors.hpp"
#include "npc_types.hpp"
#include "observers.hpp"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>

class NPC;
class Dragon;
class Knight;
class Frog;

class FightObserver;
class AttackerVisitor;

using set_t = std::set<ptr<NPC>>;

class NPC : public std::enable_shared_from_this<NPC> {
  protected:
    mutable std::mutex mtx;
    NpcType type;
    char letter;
    std::string name{""};
    int x{0};
    int y{0};
    bool alive{true};
    unsigned int move_distance{0};
    unsigned int kill_distance{0};

    std::unordered_set<NpcType> enemies;
    std::vector<ptr<FightObserver>> observers;

  public:
    NPC(NpcType t, const char letter, const std::string &name, int x, int y);

    NpcType get_type() const;
    std::pair<int, int> get_position() const;
    unsigned int get_move_distance() const;
    char get_letter() const;
    std::unordered_set<NpcType> get_enemies() const;
    bool is_alive() const;
    virtual bool is_close(const ptr<NPC> &other) const;

    void set_move_distance(unsigned int distance);
    void set_kill_distance(unsigned int distance);
    void set_enemies(const std::unordered_set<NpcType> &en);

    void move(int shift_x, int shift_y, int max_x, int max_y);
    void must_die();

    unsigned int throw_dice() const noexcept;

    void subscribe(const ptr<FightObserver> &observer);
    void fight_notify(const ptr<NPC> defender) const;

    virtual void accept(ptr<AttackerVisitor> &visitor) = 0;
    virtual void print() = 0;

    virtual void save(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};

#endif // NPC_HPP