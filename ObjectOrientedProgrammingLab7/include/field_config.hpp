#pragma once
#include "npc.hpp"
#include <nlohmann/json.hpp>

class FieldConfig;
class JsonFieldConfig;
class FieldConfigHandler;
struct NpcFieldConfigData;

struct NpcFieldConfigData {
    std::string name;
    NpcType type;
    int x;
    int y;
};

class FieldConfigHandler {
  public:
    static bool file_path_has_extension(const std::string &file_path,
                                        const std::string &extension) {
        std::filesystem::path path(file_path);
        return path.extension() == extension;
    }

    static std::shared_ptr<FieldConfig>
    create_config(const std::string &file_path) {
        if (file_path_has_extension(file_path, ".json")) {
            return JsonFieldConfig::create(file_path);
        } else {
            throw std::runtime_error("Invalid config path!");
        }
    }
};

class FieldConfig : std::enable_shared_from_this<FieldConfig> {
  public:
    virtual int get_field_max_x() = 0;
    virtual int get_field_max_y() = 0;
    virtual int get_field_min_x() = 0;
    virtual int get_field_min_y() = 0;
    virtual std::vector<NpcFieldConfigData> get_field() = 0;
};

class JsonFieldConfig : public FieldConfig {

  private:
    explicit JsonFieldConfig(const std::string &file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open configuration file: " +
                                     file_path);
        }
        file >> field_config;
    }

  public:
    using json = nlohmann::json;
    json field_config;

    static std::shared_ptr<FieldConfig> create(const std::string &file_path) {
        return std::static_pointer_cast<FieldConfig>(
            std::make_shared<JsonFieldConfig>(file_path));
    }

    JsonFieldConfig() = delete;

    int get_field_size_property(const std::string &property) {
        if (!field_config.contains(property) ||
            !field_config[property].is_number()) {
            throw std::runtime_error("Not found in configuration or not "
                                     "integer in configuration: 'field_max_x'");
        }
        return field_config.at(property).get<int>();
    }
    int get_field_max_x() override {
        return get_field_size_property("field_max_x");
    }

    int get_field_max_y() override {
        return get_field_size_property("field_max_y");
    }

    int get_field_min_x() override {
        return get_field_size_property("field_min_x");
    }

    int get_field_min_y() override {
        return get_field_size_property("field_min_y");
    }

    std::vector<NpcFieldConfigData> get_field() override {
        std::vector<NpcFieldConfigData> npcs_data;
        if (!field_config.contains("field")) {
            throw std::runtime_error("Not found in configuration: 'field'");
        }
        if (!field_config.at("field").is_array()) {
            throw std::runtime_error("Not array in configuration: 'field'");
        }

        for (const auto &npc : field_config.at("field")) {
            if (!npc.contains("name") || !npc.at("name").is_string()) {
                throw std::runtime_error("Not found in configuration or not "
                                         "string in configuration: 'name'");
            }
            if (!npc.contains("type") || !npc.at("type").is_string()) {
                throw std::runtime_error("Not found in configuration or not "
                                         "string in configuration: 'type'");
            }
            if (!npc.contains("x") || !npc.at("x").is_number()) {
                throw std::runtime_error("Not found in configuration or not "
                                         "integer in configuration: 'x'");
            }
            if (!npc.contains("y") || !npc.at("y").is_number()) {
                throw std::runtime_error("Not found in configuration or not "
                                         "integer in configuration: 'y'");
            }
            NpcFieldConfigData npc_data = {
                npc.at("name").get<std::string>(),
                StringToNpcType.at(npc.at("type").get<std::string>()),
                npc.at("x").get<int>(), npc.at("y").get<int>()};
            npcs_data.push_back(npc_data);
        }
        return npcs_data;
    }
};