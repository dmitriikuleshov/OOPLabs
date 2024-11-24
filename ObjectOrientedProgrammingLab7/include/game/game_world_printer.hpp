#ifndef GAME_WORLD_PRINTER_HPP
#define GAME_WORLD_PRINTER_HPP

#include "npc.hpp"
#include <chrono>
#include <mutex>
#include <thread>

class GameWorldPrinter {
  private:
    std::mutex &print_mutex;
    int max_x, max_y;
    std::vector<std::vector<std::string>> field;
    const std::vector<ptr<NPC>> &npcs;

    void print_horizontal() {
        for (size_t i = 0; i < (max_y + 1) * 3; ++i) {
            std::cout << ".";
        }
        std::cout << '\n';
    }

    void load_field() {
        for (auto &row : field) {
            for (auto &cell : row) {
                cell = " ";
            }
        }

        for (const auto &npc : npcs) {
            auto [x, y] = npc->get_position();
            if (npc->is_alive()) {
                field[x][y] = npc->get_letter();
            } else {
                field[x][y] = 'X';
            }
        }
    }

    void print_in_console() {
        print_horizontal();

        for (const auto &row : field) {
            std::cout << "|>";
            for (const auto &cell : row) {
                std::cout << " " + cell + " ";
            }
            std::cout << "<|\n";
        }
        print_horizontal();
    }

  public:
    GameWorldPrinter(const std::vector<ptr<NPC>> &npcs, int max_x, int max_y,
                     std::mutex &print_mutex)
        : npcs(npcs), max_x(max_x), max_y(max_y), print_mutex(print_mutex) {
        field = std::vector<std::vector<std::string>>(
            max_x + 1, std::vector<std::string>(max_y + 1, " "));
    }

    GameWorldPrinter() = delete;

    static ptr<GameWorldPrinter> create(const std::vector<ptr<NPC>> &npcs,
                                        int max_x, int max_y,
                                        std::mutex &print_mutex) {
        return std::make_shared<GameWorldPrinter>(npcs, max_x, max_y,
                                                  print_mutex);
    }
    void start_printing_field() {
        while (true) {
            std::lock_guard<std::mutex> lck(print_mutex);
            load_field();
            print_in_console();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

#endif // GAME_WORLD_PRINTER_HPP