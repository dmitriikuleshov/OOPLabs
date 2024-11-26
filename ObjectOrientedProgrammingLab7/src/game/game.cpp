#include "game.hpp"

void Game::stop() { stop_flag->store(true); }

Game::Game() {
    stop_flag = std::make_shared<std::atomic<bool>>(false);
    world_conf = WorldConfigurator::create();
    PrintManager::get().initialize(world_conf, stop_flag);
    MoveManager::get().initialize(world_conf, stop_flag);
    FightManager::get().initialize(world_conf, stop_flag);
}

void Game::run() {
    fight_thread = std::thread(std::ref(FightManager::get()));
    move_thread = std::thread(std::ref(MoveManager::get()));
    print_thread = std::thread(std::ref(PrintManager::get()));

    std::this_thread::sleep_for(std::chrono::seconds(10));
    stop();

    print_thread.join();
    move_thread.join();
    fight_thread.join();
}