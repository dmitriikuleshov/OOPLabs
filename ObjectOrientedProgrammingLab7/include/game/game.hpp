#ifndef GAME_HPP
#define GAME_HPP

#include "game_world_manager.hpp"
#include "game_world_printer.hpp"
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
    ptr<GameWorldManager> gwm;
    std::queue<FightEvent> events;
    std::shared_mutex mtx;
    std::mutex init_mtx;

    FightManager() = default;

  public:
    // Singleton
    static FightManager &get() {
        static FightManager instance;
        return instance;
    }

    void initialize(ptr<GameWorldManager> &world_manager) {
        std::lock_guard<std::mutex> lock(init_mtx);
        if (!gwm) {
            gwm = world_manager;
        }
    }

    void add_event(FightEvent &&event) {
        std::lock_guard<std::shared_mutex> lock(mtx);
        events.push(std::move(event));
    }

    std::optional<FightEvent> get_event() {
        std::optional<FightEvent> event;
        std::lock_guard<std::shared_mutex> lock(mtx);
        if (!events.empty()) {
            event = events.front();
            events.pop();
        }
        return event;
    }

    void operator()() {
        while (true) {
            auto event = get_event();

            if (event) {
                auto attacker = event->attacker;
                auto defender = event->defender;
                if (attacker->is_alive() && defender->is_alive()) {
                    auto visitor =
                        gwm->get_attacker_visitor(attacker->get_type());
                    defender->accept(visitor);
                }
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }
};

class GameMoveManager {
  public:
    const std::vector<ptr<NPC>> &npcs;
    std::unordered_map<NpcType, ptr<AttackerVisitor>> attacker_visitors;
    int max_x;
    int max_y;
    std::mutex &mtx;

    GameMoveManager(const std::vector<ptr<NPC>> &npcs, int max_x, int max_y,
                    std::mutex &mutex)
        : npcs(npcs), max_x(max_x), max_y(max_y), mtx(mutex) {}

    GameMoveManager() = delete;

    static ptr<GameMoveManager> create(const std::vector<ptr<NPC>> &npcs,
                                       int max_x, int max_y, std::mutex &mtx) {
        return std::make_shared<GameMoveManager>(npcs, max_x, max_y, mtx);
    }

    void prepare_for_fight() {
        for (auto npc : npcs) {
            for (auto other : npcs) {
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
        for (auto npc : npcs) {
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

    void start_moving() {
        while (true) {
            std::lock_guard<std::mutex> lck(mtx);
            move_npcs();
            // lets fight;
            prepare_for_fight();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

class Game {
  private:
    std::thread fight_thread;
    std::thread move_thread;
    std::thread print_thread;
    std::mutex print_mutex;
    std::mutex move_mutex;
    ptr<GameWorldManager> gwm;
    ptr<GameMoveManager> game_move_manager;
    ptr<GameWorldPrinter> printer;
    std::vector<ptr<NPC>> npcs;
    std::atomic<bool> stop_flag;
    int max_x;
    int max_y;

  public:
    Game() : stop_flag(false) {
        gwm = GameWorldManager::create();
        npcs = gwm->get_npcs();
        max_x = gwm->get_max_x();
        max_y = gwm->get_max_y();
        printer = GameWorldPrinter::create(npcs, max_x, max_y, print_mutex);
        game_move_manager =
            GameMoveManager::create(npcs, max_x, max_y, move_mutex);
        FightManager::get().initialize(gwm);
    }

    void run() {
        fight_thread = std::thread(std::ref(FightManager::get()));
        move_thread =
            std::thread([this]() { game_move_manager->start_moving(); });
        print_thread =
            std::thread([this]() { printer->start_printing_field(); });

        std::this_thread::sleep_for(std::chrono::seconds(30));

        print_thread.join();
        move_thread.join();
        fight_thread.join();
    }
};

#endif // GAME_HPP