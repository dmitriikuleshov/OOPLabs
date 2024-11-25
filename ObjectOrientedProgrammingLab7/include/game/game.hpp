#ifndef GAME_HPP
#define GAME_HPP

#include "print_manager.hpp"
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

class MoveManager {
  private:
    ptr<WorldConfigurator> world_conf;
    ptr<const std::atomic<bool>> stop_flag;
    int max_x;
    int max_y;

    std::mutex init_mtx;
    MoveManager() = default;

  public:
    // Singleton
    static MoveManager &get() {
        static MoveManager instance;
        return instance;
    }

    void initialize(ptr<WorldConfigurator> &wc,
                    const ptr<const std::atomic<bool>> &stop) {
        std::lock_guard<std::mutex> lock(init_mtx);
        stop_flag = stop;
        world_conf = wc;
        max_x = world_conf->get_max_x();
        max_y = world_conf->get_max_y();
    }

    void prepare_for_fight() {
        for (auto npc : world_conf->npcs) {
            for (auto other : world_conf->npcs) {
                if (other != npc) {
                    if (npc->is_alive() && other->is_alive() &&
                        npc->is_close(other)) {
                        FightManager::get().add_event({npc, other});
                    }
                }
            }
        }
    }

    void move_npcs() {
        int move_distance;
        for (auto npc : world_conf->npcs) {
            move_distance = npc->get_move_distance();
            if (npc->is_alive()) {
                int shift_x =
                    (std::rand() % (2 * move_distance + 1)) - move_distance;
                int shift_y =

                    (std::rand() % (2 * move_distance + 1)) - move_distance;
                npc->move(shift_x, shift_y, max_x, max_y);
            }
        }
    }

    void operator()() {
        while (!(stop_flag && stop_flag->load())) {
            move_npcs();
            // lets fight;
            prepare_for_fight();
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
};

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