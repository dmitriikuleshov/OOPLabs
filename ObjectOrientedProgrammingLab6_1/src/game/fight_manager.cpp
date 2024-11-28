#include "fight_manager.hpp"

FightManager &FightManager::get() {
    static FightManager instance;
    return instance;
}

void FightManager::initialize(ptr<WorldConfigurator> &wc,
                              const ptr<const std::atomic<GameState>> &stop) {
    std::lock_guard<std::mutex> lock(init_mtx);
    game_state = stop;
    world_conf = wc;
}

void FightManager::add_event(FightEvent &&event) {
    std::lock_guard<std::shared_mutex> lock(event_mtx);
    events.push(std::move(event));
}

std::optional<FightEvent> FightManager::get_event() {
    std::optional<FightEvent> event;
    std::lock_guard<std::shared_mutex> lock(event_mtx);
    if (!events.empty()) {
        event = events.front();
        events.pop();
    }
    return event;
}

void FightManager::operator()() {
    while (game_state->load() == GameState::Running) {
        auto event = get_event();

        if (event) {
            auto attacker = event->attacker;
            auto defender = event->defender;
            if (attacker->is_alive() && defender->is_alive()) {
                auto visitor =
                    world_conf->get_attacker_visitor(attacker->get_type());
                defender->accept(visitor);
                attacker->fight_notify(defender);
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
}