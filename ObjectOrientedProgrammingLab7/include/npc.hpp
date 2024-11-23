#pragma once
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
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
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType { UnknownType = 0, DragonType = 1, KnightType = 2, FrogType = 3 };

// const std::unordered_map<NpcType, std::string> NpcTypeString = {
//     {NpcType::UnknownType, "UnknownType"},
//     {NpcType::DragonType, "DragonType"},
//     {NpcType::KnightType, "KnightType"},
//     {NpcType::FrogType, "FrogType"}};

const std::unordered_map<std::string, NpcType> StringToNpcType = {
    {"UnknownType", NpcType::UnknownType},
    {"DragonType", NpcType::DragonType},
    {"KnightType", NpcType::KnightType},
    {"FrogType", NpcType::FrogType}};

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<NPC> attacker,
                          const std::shared_ptr<NPC> defender, bool win) = 0;
};

class NPC : public std::enable_shared_from_this<NPC> {
  protected:
    mutable std::mutex mtx;
    NpcType type;
    std::string str_type;
    std::string name{""};
    int x{0};
    int y{0};
    bool alive{true};
    unsigned int move_distance{0};
    unsigned int kill_distance{0};

    std::unordered_set<NpcType> enemies;
    std::vector<std::shared_ptr<IFightObserver>> observers;

  public:
    NPC(NpcType t, const std::string &name, int _x, int _y);
    NPC(NpcType t, std::istream &is);

    NpcType get_type() const;
    std::pair<int, int> get_position() const;
    unsigned int get_move_distance() const;
    std::unordered_set<NpcType> get_enemies() const;
    bool is_alive() const;
    virtual bool is_close(const std::shared_ptr<NPC> &other) const;

    void set_move_distance(unsigned int distance);
    void set_kill_distance(unsigned int distance);
    void set_enemies(const std::unordered_set<NpcType> &en);

    void move(int shift_x, int shift_y, int max_x, int max_y);
    void must_die();

    unsigned int throw_dice() const noexcept;

    void subscribe(const std::shared_ptr<IFightObserver> &observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win) const;

    virtual void accept(AttackerVisitor &visitor) = 0;
    virtual void print() = 0;

    virtual void save(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};