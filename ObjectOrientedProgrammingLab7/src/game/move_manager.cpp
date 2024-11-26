#include "move_manager.hpp"

MoveManager &MoveManager::get() {
    static MoveManager instance;
    return instance;
}

void MoveManager::initialize(ptr<WorldConfigurator> &wc,
                             const ptr<const std::atomic<bool>> &stop) {
    std::lock_guard<std::mutex> lock(init_mtx);
    stop_flag = stop;
    world_conf = wc;
    max_x = world_conf->get_max_x();
    max_y = world_conf->get_max_y();
}

void MoveManager::prepare_for_fight() {
    for (auto npc : world_conf->npcs) {
        for (auto other : world_conf->npcs) {
            if (other != npc) {
                if (npc->is_alive() && other->is_alive() &&
                    npc->is_close(other)) {
                    FightManager::get().add_event({npc, other});
                }
            }
        }
    }
}

void MoveManager::move_npcs() {
    int move_distance;
    for (auto npc : world_conf->npcs) {
        move_distance = npc->get_move_distance();
        if (npc->is_alive()) {
            int shift_x =
                (std::rand() % (2 * move_distance + 1)) - move_distance;
            int shift_y =

                (std::rand() % (2 * move_distance + 1)) - move_distance;
            npc->move(shift_x, shift_y, max_x, max_y);
        }
    }
}

void MoveManager::operator()() {
    while (!(stop_flag && stop_flag->load())) {
        move_npcs();
        // lets fight;
        prepare_for_fight();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
