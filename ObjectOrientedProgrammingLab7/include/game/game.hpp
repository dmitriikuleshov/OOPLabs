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
    std::thread fight_thread;
    std::thread move_thread;
    std::thread print_thread;
    ptr<std::atomic<GameState>> game_state;
    ptr<WorldConfigurator> world_conf;
    int time_limit;
    void stop();

  public:
    Game();
    void run();
};

#endif // GAME_HPP