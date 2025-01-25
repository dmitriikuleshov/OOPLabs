#include "print_manager.hpp"

PrintManager &PrintManager::get() {
    static PrintManager instance;
    return instance;
}

void PrintManager::initialize(ptr<WorldConfigurator> &wc,
                              const ptr<const std::atomic<GameState>> &stop) {
    std::lock_guard<std::mutex> lock(init_mtx);
    game_state = stop;
    world_conf = wc;
    max_x = world_conf->get_max_x();
    max_y = world_conf->get_max_y();
    field = std::vector<std::vector<std::string>>(
        max_x + 1, std::vector<std::string>(max_y + 1, " "));
}

void PrintManager::operator()() {
    while (game_state->load() == GameState::Running) {
        load_field();
        print_world();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    print_winners();
}

void PrintManager::print_horizontal() {
    for (size_t i = 0; i < (max_y + 1) * 3 + 4; ++i) {
        std::cout << ".";
    }
    std::cout << '\n';
}

void PrintManager::load_field() {
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

void PrintManager::print_world() {
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

void PrintManager::print_winners() {
    std::vector<ptr<NPC>> survivors;
    for (const auto &npc : world_conf->npcs) {
        if (npc->is_alive()) {
            survivors.push_back(npc);
        }
    }

    std::cout << std::endl;
    std::cout
        << "|===========================================================|\n";
    std::cout
        << "|                         GAME OVER                         |\n";
    std::cout
        << "|===========================================================|\n";

    switch (survivors.size()) {
    case 0:
        std::cout << "No survivors! The battlefield is silent...\n";
        std::cout << "---------------------------------------------------------"
                     "----\n";
        break;
    case 1:
        std::cout << "                *** ULTIMATE WINNER ***              \n";
        std::cout << "---------------------------------------------------------"
                     "----\n";
        break;
    default:
        std::cout
            << "|                       TIMEOUT REACHED                     |"
            << std::endl;
        std::cout << "|                       SURVIVING NPCs ("
                  << survivors.size() << ")                  |\n";
        std::cout << "---------------------------------------------------------"
                     "----\n";
    }

    for (const auto &npc : survivors) {
        npc->print();
    }

    if (survivors.size() > 1) {
        std::cout << "The battle ends, but the survivors live to fight another "
                     "day!\n";
    }

    std::cout
        << "=============================================================\n";
    std::cout << std::endl;
}