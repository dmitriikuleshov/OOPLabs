#include "game.hpp"

void Game::stop() { game_state->store(GameState::Timeout); }

Game::Game() {
    time_limit = 30;
    game_state = std::make_shared<std::atomic<GameState>>(GameState::Running);
    world_conf = WorldConfigurator::create();
    PrintManager::get().initialize(world_conf, game_state);
    MoveManager::get().initialize(world_conf, game_state);
    FightManager::get().initialize(world_conf, game_state);
}

void Game::run() {
    fight_thread = std::thread(std::ref(FightManager::get()));
    move_thread = std::thread(std::ref(MoveManager::get()));
    print_thread = std::thread(std::ref(PrintManager::get()));

    auto start_time = std::chrono::steady_clock::now();
    const auto timeout = std::chrono::seconds(time_limit);

    while (game_state->load() == GameState::Running) {
        auto elapsed_time = std::chrono::steady_clock::now() - start_time;
        if (elapsed_time >= timeout) {
            stop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    print_thread.join();
    move_thread.join();
    fight_thread.join();
}