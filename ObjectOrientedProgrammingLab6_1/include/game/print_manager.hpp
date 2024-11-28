#ifndef PRINT_MANAGER_HPP
#define PRINT_MANAGER_HPP

#include "game_state.hpp"
#include "npc.hpp"
#include "world_configurator.hpp"
#include <chrono>
#include <mutex>
#include <thread>

class PrintManager {
  public:
    static PrintManager &get();
    void initialize(ptr<WorldConfigurator> &wc,
                    const ptr<const std::atomic<GameState>> &stop);
    void operator()();

  private:
    ptr<const std::atomic<GameState>> game_state;
    ptr<WorldConfigurator> world_conf;
    int max_x;
    int max_y;

    std::vector<std::vector<std::string>> field;

    std::mutex init_mtx;
    PrintManager() = default;

    void print_horizontal();
    void load_field();
    void print_world();
    void print_winners();
};

#endif // PRINT_MANAGER_HPP