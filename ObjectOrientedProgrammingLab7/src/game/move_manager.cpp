#include "move_manager.hpp"

MoveManager &MoveManager::get() {
    static MoveManager instance;
    return instance;
}

void MoveManager::initialize(ptr<WorldConfigurator> &wc,
                             const ptr<std::atomic<GameState>> &stop) {
    std::lock_guard<std::mutex> lock(init_mtx);
    game_state = stop;
    world_conf = wc;
    max_x = world_conf->get_max_x();
    max_y = world_conf->get_max_y();
}

void MoveManager::prepare_for_fight() {
    for (auto npc : world_conf->npcs) {
        for (auto other : world_conf->npcs) {
            if (other != npc && npc->is_alive() && other->is_alive() &&
                npc->is_close(other)) {
                if (npc->throw_dice() > other->throw_dice()) {
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

void MoveManager::update_game_state() {
    size_t counter;
    for (auto npc : world_conf->npcs) {
        if (npc->is_alive()) {
            ++counter;
        }
    }
    switch (counter) {
    case 0:
        game_state->store(GameState::AllDead);
        break;
    case 1:
        game_state->store(GameState::OneNpcLeft);
        break;
    }
}

void MoveManager::operator()() {
    while (game_state->load() == GameState::Running) {
        move_npcs();
        // lets fight;
        prepare_for_fight();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
