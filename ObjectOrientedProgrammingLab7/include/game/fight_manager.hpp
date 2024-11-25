
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
  private:
    ptr<const std::atomic<bool>> stop_flag;
    ptr<WorldConfigurator> world_conf;
    std::queue<FightEvent> events;
    std::shared_mutex event_mtx;

    std::mutex init_mtx;
    FightManager() = default;

  public:
    // Singleton
    static FightManager &get() {
        static FightManager instance;
        return instance;
    }

    void initialize(ptr<WorldConfigurator> &wc,
                    const ptr<const std::atomic<bool>> &stop) {
        std::lock_guard<std::mutex> lock(init_mtx);
        stop_flag = stop;
        world_conf = wc;
    }

    void add_event(FightEvent &&event) {
        std::lock_guard<std::shared_mutex> lock(event_mtx);
        events.push(std::move(event));
    }

    std::optional<FightEvent> get_event() {
        std::optional<FightEvent> event;
        std::lock_guard<std::shared_mutex> lock(event_mtx);
        if (!events.empty()) {
            event = events.front();
            events.pop();
        }
        return event;
    }

    void operator()() {
        while (!(stop_flag && stop_flag->load())) {
            auto event = get_event();

            if (event) {
                auto attacker = event->attacker;
                auto defender = event->defender;
                if (attacker->is_alive() && defender->is_alive()) {
                    auto visitor =
                        world_conf->get_attacker_visitor(attacker->get_type());
                    defender->accept(visitor);
                }
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
        }
    }
};

#endif // FIGHT_MANAGER_HPP