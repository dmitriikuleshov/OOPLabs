#ifndef GAME_WORLD_MANAGER_HPP
#define GAME_WORLD_MANAGER_HPP

#include <cstdlib>
#include <filesystem>
#include <string>

#include "npc.hpp"

#include "field_config.hpp"
#include "npc_properties_config.hpp"

#include "attacker_visitors.hpp"
#include "factories.hpp"

class GameWorldManager {
  public:
    GameWorldManager() {
        define_npc_properties_config();
        define_field_config();
        define_attacker_visitors();
        define_factories();
        define_npc_generator();
        define_field_size();
        generate_npcs();
    }

    static ptr<GameWorldManager> create() {
        return std::make_shared<GameWorldManager>();
    }

    std::vector<ptr<NPC>> get_npcs() { return npcs; }
    std::unordered_map<NpcType, ptr<AttackerVisitor>> get_attacker_visitors() {
        return attacker_visitors;
    }
    int get_max_x() { return field_max_x; }
    int get_max_y() { return field_max_y; }

    //  private:
    // npc config
    std::string npc_properties_config_file_path_env = "NPC_PROPERTIES_CONFIG";
    std::string npc_properties_config_file_path;
    ptr<NpcPropertiesConfig> npc_properties_config;

    // field config
    std::string field_config_file_path_env = "FIELD_CONFIG";
    std::string field_config_file_path;

    ptr<FieldConfig> field_config;
    std::vector<NpcFieldConfigData> npcs_field_data;

    // field size
    int field_max_x;
    int field_max_y;

    // npc interraction
    std::unordered_map<NpcType, ptr<NpcFactory>> npc_factories;
    ptr<NpcGenerator> npc_generator;
    std::unordered_map<NpcType, ptr<AttackerVisitor>> attacker_visitors;
    std::vector<ptr<NPC>> npcs;

    // Methods
    std::string get_config_file_path(const std::string &env) {
        const char *path_raw = std::getenv(env.c_str());
        if (!path_raw) {
            throw std::runtime_error(
                "Could not get config file path using environment variable");
        }
        return std::string(path_raw);
    }

    void define_npc_properties_config() {
        npc_properties_config_file_path =
            get_config_file_path(npc_properties_config_file_path_env);
        npc_properties_config = NpcPropertiesConfigHandler::create_config(
            npc_properties_config_file_path);
        if (!npc_properties_config) {
            throw std::runtime_error(
                "Error while trying to get npc_properties_config");
        }
    }

    void define_npc_generator() {
        npc_generator = NpcGenerator::create(npc_factories);
        if (!npc_generator) {
            throw std::runtime_error("Error while trying to get npc_generator");
        }
    }

    void define_field_config() {
        field_config_file_path =
            get_config_file_path(field_config_file_path_env);
        field_config =
            FieldConfigHandler::create_config(field_config_file_path);
        if (!field_config) {
            throw std::runtime_error("Error while trying to get field_config");
        }
    }

    void define_attacker_visitors() {
        attacker_visitors[KnightType] =
            KnightAttackerVisitor::create(npc_properties_config);
        attacker_visitors[DragonType] =
            DragonAttackerVisitor::create(npc_properties_config);
        attacker_visitors[FrogType] =
            FrogAttackerVisitor::create(npc_properties_config);
    }

    void define_factories() {
        npc_factories[KnightType] =
            KnightFactory::create(npc_properties_config);
        npc_factories[DragonType] =
            DragonFactory::create(npc_properties_config);
        npc_factories[FrogType] = FrogFactory::create(npc_properties_config);
    }

    void define_field_size() {
        field_max_x = field_config->get_field_max_x();
        field_max_y = field_config->get_field_max_y();
    }

    void generate_npcs() {
        npcs_field_data = field_config->get_field();
        for (const auto &data : npcs_field_data) {
            auto npc =
                npc_generator->create_npc(data.type, data.name, data.x, data.y);
            if (!npc) {
                throw std::runtime_error("Error creating npc with generator");
            }
            npcs.push_back(npc);
        }
    }
};

#endif // GAME_WORLD_MANAGER_HPP