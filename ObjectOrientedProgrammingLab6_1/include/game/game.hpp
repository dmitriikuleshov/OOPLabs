#ifndef GAME_HPP
#define GAME_HPP

#include "fight_manager.hpp"
#include "game_state.hpp"
#include "move_manager.hpp"
#include "print_manager.hpp"
#include "world_configurator.hpp"
#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>

class Game {
  private:
    ptr<WorldConfigurator> world_conf;
    void save(const std::string &filename);
    void fight();
    bool all_dead();
    void set_kill_distance(int distance);
    int distance_increase = 10;

  public:
    Game();
    void run();
};

#endif // GAME_HPP