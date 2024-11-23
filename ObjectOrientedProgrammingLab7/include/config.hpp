#pragma once
#include "npc.hpp"
#include <nlohmann/json.hpp>

class INpcConfig;
class JsonConfig;
class ConfigHandler;

class ConfigHandler {
  public:
    static bool file_path_has_extension(const std::string &file_path,
                                        const std::string &extension) {
        std::filesystem::path path(file_path);
        return path.extension() == extension;
    }

    static std::shared_ptr<INpcConfig>
    create_config(const std::string &file_path) {
        if (file_path_has_extension(file_path, ".json")) {
            return JsonNpcConfig::create(file_path);
        } else {
            throw std::runtime_error("Invalid config path!");
        }
    }
};

class INpcConfig : std::enable_shared_from_this<INpcConfig> {
  public:
    virtual int get_move_distance(const std::string &npc_type_name) = 0;
    virtual int get_kill_distance(const std::string &npc_type_name) = 0;
    virtual std::unordered_set<NpcType>
    get_enemies(const std::string &npc_type_name) = 0;
};

class JsonNpcConfig : public INpcConfig {

  private:
    explicit JsonNpcConfig(const std::string &file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open configuration file: " +
                                     file_path);
        }
        file >> npc_config;
    }

  public:
    using json = nlohmann::json;
    json npc_config;

    static std::shared_ptr<INpcConfig> create(const std::string &file_path) {
        return std::static_pointer_cast<INpcConfig>(
            std::make_shared<JsonNpcConfig>(file_path));
    }

    JsonNpcConfig() = delete;

    void check_for_npc_in_config(const std::string &npc_type_name) {
        if (!npc_config.contains(npc_type_name)) {
            throw std::runtime_error("NPC type not found in configuration: " +
                                     npc_type_name);
        }
    }

    int get_move_distance(const std::string &npc_type_name) override {
        check_for_npc_in_config(npc_type_name);
        const auto &npc_data = npc_config.at(npc_type_name);
        if (!npc_data.contains("move_distance") ||
            !npc_data["move_distance"].is_number()) {
            throw std::runtime_error(
                "Missing or invalid 'move_distance' for NPC: " + npc_type_name);
        }
        return npc_data.at("move_distance").get<int>();
    }

    int get_kill_distance(const std::string &npc_type_name) override {
        check_for_npc_in_config(npc_type_name);
        const auto &npc_data = npc_config.at(npc_type_name);
        if (!npc_data.contains("kill_distance") ||
            !npc_data["kill_distance"].is_number()) {
            throw std::runtime_error(
                "Missing or invalid 'kill_distance' for NPC: " + npc_type_name);
        }
        return npc_data.at("kill_distance").get<int>();
    }

    std::unordered_set<NpcType>
    get_enemies(const std::string &npc_type_name) override {
        check_for_npc_in_config(npc_type_name);
        const auto &npc_data = npc_config.at(npc_type_name);
        if (!npc_data.contains("enemies") || !npc_data["enemies"].is_array()) {
            throw std::runtime_error("Missing or invalid 'enemies' for NPC: " +
                                     npc_type_name);
        }

        std::unordered_set<NpcType> enemies;
        for (const auto &enemy : npc_data.at("enemies")) {
            if (!enemy.is_string()) {
                throw std::runtime_error(
                    "Invalid enemy type in 'enemies' for NPC: " +
                    npc_type_name);
            }
            const std::string enemy_type_name = enemy.get<std::string>();
            if (StringToNpcType.find(enemy_type_name) ==
                StringToNpcType.end()) {
                throw std::runtime_error("Unknown enemy type: " +
                                         enemy_type_name);
            }
            enemies.insert(StringToNpcType.at(enemy_type_name));
        }
        return enemies;
    }
};