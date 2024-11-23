#pragma once
#include <cstdlib>
#include <filesystem>
#include <string>

#include "npc.hpp"

#include "field_config.hpp"
#include "npc_properties_config.hpp"

#include "factory.hpp"
#include "visitor.hpp"

class GameWorldManager {
  public:
    GameWorldManager() {
        npc_properties_config = NpcPropertiesConfigHandler::create_config(
            npc_properties_config_file_path);
        field_config =
            FieldConfigHandler::create_config(field_config_file_path);
        define_attacker_visitors();
        define_factories();
        npc_generator = NpcGenerator::create(npc_factories);
        generate_npcs();
        define_field_size();
    }

    std::vector<std::shared_ptr<NPC>> get_npcs() { return npcs; }
    int get_max_x() { return field_max_x; }
    int get_max_y() { return field_max_y; }

  private:
    // npc config
    std::string npc_properties_config_file_path_env = "NPC_PROPERTIES_CONFIG";
    std::string npc_properties_config_file_path =
        get_config_file_path(npc_properties_config_file_path_env);
    std::shared_ptr<NpcPropertiesConfig> npc_properties_config;

    // field config
    std::string field_config_file_path_env = "FIELD_CONFIG";
    std::string field_config_file_path =
        get_config_file_path(field_config_file_path_env);
    std::shared_ptr<FieldConfig> field_config;
    std::vector<NpcFieldConfigData> npcs_field_data;

    // field size
    int field_max_x;
    int field_max_y;

    // npc interraction
    std::unordered_map<NpcType, std::shared_ptr<NpcFactory>> npc_factories;
    std::shared_ptr<NpcGenerator> npc_generator;
    std::unordered_map<NpcType, AttackerVisitor> attacker_visitors;
    std::vector<std::shared_ptr<NPC>> npcs;

    // Methods
    std::string get_config_file_path(const std::string &env) {
        const char *path_raw = std::getenv(env.c_str());
        if (!path_raw) {
            throw std::runtime_error(
                "Could not get config file path using environment variable");
        }
        return std::string(path_raw);
    }

    void define_attacker_visitors() {
        attacker_visitors[KnightType] =
            KnightAttackerVisitor(npc_properties_config);
        attacker_visitors[DragonType] =
            DragonAttackerVisitor(npc_properties_config);
        attacker_visitors[FrogType] =
            FrogAttackerVisitor(npc_properties_config);
    }

    void define_factories() {
        npc_factories[KnightType] = KnightFactory::create();
        npc_factories[DragonType] = DragonFactory::create();
        npc_factories[FrogType] = FrogFactory::create();
    }

    void define_field_size() {
        field_max_x = field_config->get_field_max_x();
        field_max_y = field_config->get_field_max_y();
    }

    void generate_npcs() {
        for (const auto &data : npcs_field_data) {
            auto npc =
                npc_generator->create_npc(data.type, data.name, data.x, data.y);
            npcs.push_back(npc);
        }
    }
};

class Printer {
  private:
    int max_x, max_y;
    std::vector<std::vector<std::string>> field;
    Printer(int max_x, int max_y) : max_x(max_x), max_y(max_y) {}

  public:
    static std::shared_ptr<Printer> create(int max_x, int max_y) {
        return std::make_shared<Printer>(max_x, max_y);
    }
    void print_field(const std::vector<std::shared_ptr<NPC>> &npcs) {
        for (auto &row : field) {
            for (auto &cell : row) {
                cell = " ";
            }
        }

        for (const auto &npc : npcs) {
            auto [x, y] = npc->get_position();
            field[x][y] = npc->get_letter();
        }

        for (const auto &row : field) {
            for (const auto &cell : row) {
                std::cout << cell;
            }
            std::cout << '\n';
        }
    }
};

class Game {
  private:
    GameWorldManager game_world_manager = GameWorldManager();
    std::vector<std::shared_ptr<NPC>> npcs = game_world_manager.get_npcs();
    int max_x = game_world_manager.get_max_x();
    int max_y = game_world_manager.get_max_y();
    std::shared_ptr<Printer> printer = Printer::create(max_x, max_y);

  public:
    void run() { printer->print_field(npcs); }
};
