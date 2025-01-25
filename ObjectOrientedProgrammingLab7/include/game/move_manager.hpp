#ifndef MOVE_MANAGER_HPP
#define MOVE_MANAGER_HPP

#include "fight_manager.hpp"
#include "game_state.hpp"
#include "world_configurator.hpp"
#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>

class MoveManager {

  public:
    // Singleton
    static MoveManager &get();

    void initialize(ptr<WorldConfigurator> &wc,
                    const ptr<std::atomic<GameState>> &stop);

    void operator()();

  private:
    ptr<WorldConfigurator> world_conf;
    ptr<std::atomic<GameState>> game_state;
    int max_x;
    int max_y;

    std::mutex init_mtx;
    MoveManager() = default;

    void prepare_for_fight();
    void move_npcs();
    void update_game_state();
};

#endif // MOVE_MANAGER_HPP