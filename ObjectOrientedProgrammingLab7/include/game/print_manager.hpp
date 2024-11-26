#ifndef PRINT_MANAGER_HPP
#define PRINT_MANAGER_HPP

#include "npc.hpp"
#include "world_configurator.hpp"
#include <chrono>
#include <mutex>
#include <thread>

class PrintManager {
  private:
    ptr<const std::atomic<bool>> stop_flag;
    ptr<WorldConfigurator> world_conf;
    int max_x;
    int max_y;

    std::vector<std::vector<std::string>> field;

    std::mutex init_mtx;
    PrintManager() = default;

    void print_horizontal() {
        for (size_t i = 0; i < (max_y + 1) * 3 + 4; ++i) {
            std::cout << ".";
        }
        std::cout << '\n';
    }

    void load_field() {
        // std::lock_guard<std::shared_mutex> lock(world_conf->mtx);
        for (auto &row : field) {
            for (auto &cell : row) {
                cell = " ";
            }
        }

        for (const auto &npc : world_conf->npcs) {
            auto [x, y] = npc->get_position();
            if (npc->is_alive()) {
                field.at(x).at(y) = npc->get_letter();
            } else {
                field.at(x).at(y) = 'X';
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

    void print_winners() {
        std::cout << " ----------------------- WINNERS"
                     " ----------------------- \n";
        for (const auto &npc : world_conf->npcs) {
            if (npc->is_alive()) {
                npc->print();
            }
        }
    }

  public:
    static PrintManager &get() {
        static PrintManager instance;
        return instance;
    }

    void initialize(ptr<WorldConfigurator> &wc,
                    const ptr<const std::atomic<bool>> &stop) {
        // std::lock_guard<std::mutex> lock(init_mtx);
        stop_flag = stop;
        world_conf = wc;
        max_x = world_conf->get_max_x();
        max_y = world_conf->get_max_y();
        field = std::vector<std::vector<std::string>>(
            max_x + 1, std::vector<std::string>(max_y + 1, " "));
    }

    void operator()() {
        while (!(stop_flag && stop_flag->load())) {
            load_field();
            print_in_console();
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        print_winners();
    }
};

#endif // PRINT_MANAGER_HPP