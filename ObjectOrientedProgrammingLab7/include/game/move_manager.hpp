#ifndef MOVE_MANAGER_HPP
#define MOVE_MANAGER_HPP

#include "fight_manager.hpp"
#include "world_configurator.hpp"
#include <atomic>
#include <chrono>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

class MoveManager {
  private:
    ptr<WorldConfigurator> world_conf;
    ptr<const std::atomic<bool>> stop_flag;
    int max_x;
    int max_y;

    std::mutex init_mtx;
    MoveManager() = default;

  public:
    // Singleton
    static MoveManager &get() {
        static MoveManager instance;
        return instance;
    }

    void initialize(ptr<WorldConfigurator> &wc,
                    const ptr<const std::atomic<bool>> &stop) {
        std::lock_guard<std::mutex> lock(init_mtx);
        stop_flag = stop;
        world_conf = wc;
        max_x = world_conf->get_max_x();
        max_y = world_conf->get_max_y();
    }

    void prepare_for_fight() {
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

    void move_npcs() {
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

    void operator()() {
        while (!(stop_flag && stop_flag->load())) {
            move_npcs();
            // lets fight;
            prepare_for_fight();
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
};

#endif // MOVE_MANAGER_HPP