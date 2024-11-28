#include "game.hpp"

Game::Game() { world_conf = WorldConfigurator::create(); }

void Game::run() {
    std::cout << "=== Saving NPCs to File ===\n" << std::endl;
    save("npc.txt");
    std::cout << "=== Initial NPC List ===\n" << std::endl;
    for (const auto &npc : world_conf->npcs) {
        std::cout << *npc;
    }
    std::cout << std::endl;
    std::cout << "=== Starting Battles ===\n\n" << std::endl;
    for (const auto &npc : world_conf->npcs) {
        npc->set_kill_distance(20);
    }
    fight();

    std::cout << "=== Final Survivors ===" << std::endl;

    if (!all_dead()) {
        for (const auto &npc : world_conf->npcs) {
            if (npc->is_alive()) {
                std::cout << *npc;
            }
        }
    } else {
        std::cout << "No survivors remain." << std::endl;
    }
}

bool Game::all_dead() {
    size_t counter = 0;
    for (const auto &npc : world_conf->npcs) {
        if (npc->is_alive()) {
            return false;
        }
    }
    return true;
}

void Game::set_kill_distance(int distance) {
    for (const auto &npc : world_conf->npcs) {
        npc->set_kill_distance(distance);
    }
}

void Game::fight() {

    int alive_npcs_counter = world_conf->npcs.size();

    for (size_t distance = 20; (distance <= 100) && !all_dead();
         distance += 10) {
        set_kill_distance(distance);
        std::vector<ptr<NPC>> dead_list;
        for (const auto &attacker : world_conf->npcs) {
            for (const auto &defender : world_conf->npcs) {
                if ((attacker != defender) && (attacker->is_close(defender)) &&
                    attacker->is_alive() && defender->is_alive()) {
                    auto visitor =
                        world_conf->get_attacker_visitor(attacker->get_type());
                    defender->accept(visitor);
                    attacker->fight_notify(defender);
                    if (!defender->is_alive()) {
                        dead_list.push_back(defender);
                    }
                }
            }
        }
        alive_npcs_counter -= dead_list.size();
        std::cout << "\n*** Fight Results ***" << std::endl;
        std::cout << "Distance: " << distance << " meters" << std::endl;
        std::cout << "Killed: " << dead_list.size() << " NPC(s)" << std::endl;
        std::cout << "Remaining: " << alive_npcs_counter << " NPC(s)"
                  << std::endl;
        std::cout << "**********************\n" << std::endl;
    }
}

void Game::save(const std::string &filename) {
    std::ofstream fs(filename);
    fs << world_conf->npcs.size() << std::endl;
    for (auto &n : world_conf->npcs)
        n->save(fs);
    fs.flush();
    fs.close();
}