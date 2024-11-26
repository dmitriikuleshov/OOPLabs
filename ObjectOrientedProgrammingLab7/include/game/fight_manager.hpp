
#ifndef FIGHT_MANAGER_HPP
#define FIGHT_MANAGER_HPP

#include "world_configurator.hpp"
#include <atomic>
#include <chrono>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

struct FightEvent {
    ptr<NPC> attacker;
    ptr<NPC> defender;
};

class FightManager {
  public:
    // Singleton
    static FightManager &get();
    void initialize(ptr<WorldConfigurator> &wc,
                    const ptr<const std::atomic<bool>> &stop);
    void add_event(FightEvent &&event);
    void operator()();

  private:
    ptr<const std::atomic<bool>> stop_flag;
    ptr<WorldConfigurator> world_conf;
    std::queue<FightEvent> events;
    std::shared_mutex event_mtx;

    std::mutex init_mtx;
    FightManager() = default;

    std::optional<FightEvent> get_event();
};

#endif // FIGHT_MANAGER_HPP