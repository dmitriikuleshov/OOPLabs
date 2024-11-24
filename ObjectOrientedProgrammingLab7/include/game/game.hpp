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
    std::unordered_map<NpcType, ptr<AttackerVisitor>> attacker_visitors;
    std::shared_mutex mtx;

    // Приватный конструктор
    FightManager(std::unordered_map<NpcType, ptr<AttackerVisitor>> visitors)
        : attacker_visitors(std::move(visitors)) {}

  public:
    // Singleton с контролем инициализации
    static FightManager &
    get(std::optional<std::unordered_map<NpcType, ptr<AttackerVisitor>>>
            visitors = std::nullopt) {
        static FightManager instance(visitors.value_or(
            std::unordered_map<NpcType, ptr<AttackerVisitor>>{}));
        return instance;
    }

    // Добавление события
    void add_event(FightEvent &&event) {
        std::lock_guard<std::shared_mutex> lock(mtx);
        events.push(std::move(event));
    }

    // Получение AttackerVisitor по типу NPC
    ptr<AttackerVisitor> get_attacker_visitor(NpcType type) {
        std::shared_lock<std::shared_mutex> lock(mtx);
        auto it = attacker_visitors.find(type);
        return (it != attacker_visitors.end()) ? it->second : nullptr;
    }

    // Основной цикл обработки
    void operator()() {
        while (true) {
            std::optional<FightEvent> event;

            {
                std::lock_guard<std::shared_mutex> lock(mtx);
                if (!events.empty()) {
                    event = events.front();
                    events.pop();
                }
            }

            if (event) {
                if (event->attacker->is_alive()) { // Проверка на жизнь
                    if (event->defender->is_alive()) { // Проверка на жизнь
                        auto visitor =
                            get_attacker_visitor(event->attacker->get_type());
                        if (visitor) {
                            event->defender->accept(visitor);
                        }
                    }
                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
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
    ptr<GameWorldManager> game_world_manager;
    ptr<GameMoveManager> game_move_manager;
    ptr<GameWorldPrinter> printer;
    std::vector<ptr<NPC>> npcs;
    std::atomic<bool> stop_flag;
    int max_x;
    int max_y;

  public:
    Game() : stop_flag(false) {
        game_world_manager = GameWorldManager::create();
        npcs = game_world_manager->get_npcs();
        max_x = game_world_manager->get_max_x();
        max_y = game_world_manager->get_max_y();
        printer = GameWorldPrinter::create(npcs, max_x, max_y, print_mutex);
        game_move_manager =
            GameMoveManager::create(npcs, max_x, max_y, move_mutex);
    }

    void run() {
        fight_thread = std::thread(std::ref(
            FightManager::get(game_world_manager->get_attacker_visitors())));
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