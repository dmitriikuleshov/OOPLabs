#include "npc.hpp"

NPC::NPC(NpcType t, const char letter, const std::string &name, int x, int y)
    : type(t), letter(letter), name(name), x(x), y(y) {}

NpcType NPC::get_type() const {
    std::lock_guard<std::mutex> lck(mtx);
    return type;
}

std::pair<int, int> NPC::get_position() const {
    std::lock_guard<std::mutex> lck(mtx);
    return {x, y};
}

unsigned int NPC::get_move_distance() const {
    std::lock_guard<std::mutex> lck(mtx);
    return move_distance;
}

unsigned int NPC::get_kill_distance() const {
    std::lock_guard<std::mutex> lck(mtx);
    return kill_distance;
}

char NPC::get_letter() const {
    std::lock_guard<std::mutex> lck(mtx);
    return letter;
}

std::unordered_set<NpcType> NPC::get_enemies() const {
    std::lock_guard<std::mutex> lock(mtx);
    return enemies;
}

bool NPC::is_alive() const {
    std::lock_guard<std::mutex> lck(mtx);
    return alive;
}

bool NPC::is_close(const ptr<NPC> &other) const {
    auto [other_x, other_y] = other->get_position();

    std::lock_guard<std::mutex> lck(mtx);
    bool close = (std::pow(x - other_x, 2) + std::pow(y - other_y, 2)) <=
                 std::pow(kill_distance, 2);
    return close;
}

void NPC::set_move_distance(unsigned int distance) {
    std::lock_guard<std::mutex> lck(mtx);
    move_distance = distance;
}

void NPC::set_kill_distance(unsigned int distance) {
    std::lock_guard<std::mutex> lck(mtx);
    kill_distance = distance;
}

void NPC::set_enemies(const std::unordered_set<NpcType> &en) {
    std::lock_guard<std::mutex> lck(mtx);
    enemies = en;
}

void NPC::move(int shift_x, int shift_y, int max_x, int max_y) {
    std::lock_guard<std::mutex> lck(mtx);
    if ((x + shift_x >= 0) && (x + shift_x <= max_x))
        x += shift_x;
    if ((y + shift_y >= 0) && (y + shift_y <= max_y))
        y += shift_y;
}

void NPC::must_die() {
    std::lock_guard<std::mutex> lck(mtx);
    alive = false;
}

unsigned int NPC::throw_dice() const noexcept { return std::rand() % 6 + 1; }

void NPC::subscribe(const ptr<FightObserver> &observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const ptr<NPC> defender) const {
    if (!defender->is_alive()) {
        for (auto &o : observers)
            o->on_fight(std::const_pointer_cast<NPC>(shared_from_this()),
                        defender);
    }
}

void NPC::save(std::ostream &os) {
    os << name << std::endl;
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc) {
    os << npc.name << " "
       << "{ x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}
