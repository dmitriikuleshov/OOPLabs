#ifndef GAME_HPP
#define GAME_HPP

#include "fight_manager.hpp"
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
    ptr<std::atomic<bool>> stop_flag;
    ptr<WorldConfigurator> world_conf;
    void stop() { stop_flag->store(true); }

  public:
    Game() {
        stop_flag = std::make_shared<std::atomic<bool>>(false);
        world_conf = WorldConfigurator::create();
        PrintManager::get().initialize(world_conf, stop_flag);
        MoveManager::get().initialize(world_conf, stop_flag);
        FightManager::get().initialize(world_conf, stop_flag);
    }

    void run() {
        fight_thread = std::thread(std::ref(FightManager::get()));
        move_thread = std::thread(std::ref(MoveManager::get()));
        print_thread = std::thread(std::ref(PrintManager::get()));

        std::this_thread::sleep_for(std::chrono::seconds(10));
        stop();

        print_thread.join();
        move_thread.join();
        fight_thread.join();
    }
};

#endif // GAME_HPP