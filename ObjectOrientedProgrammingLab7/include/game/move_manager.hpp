#ifndef MOVE_MANAGER_HPP
#define MOVE_MANAGER_HPP

#include "fight_manager.hpp"
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
                    const ptr<const std::atomic<bool>> &stop);
    void prepare_for_fight();
    void move_npcs();
    void operator()();

  private:
    ptr<WorldConfigurator> world_conf;
    ptr<const std::atomic<bool>> stop_flag;
    int max_x;
    int max_y;

    std::mutex init_mtx;
    MoveManager() = default;
};

#endif // MOVE_MANAGER_HPP