#include "field_configs.hpp"

// JsonFieldConfig

JsonFieldConfig::JsonFieldConfig(const std::string &file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open configuration file: " +
                                 file_path);
    }
    file >> field_config;
}

ptr<FieldConfig> JsonFieldConfig::create(const std::string &file_path) {
    return std::static_pointer_cast<FieldConfig>(
        std::make_shared<JsonFieldConfig>(file_path));
}

int JsonFieldConfig::get_field_max_x() {
    return get_field_size_property("field_max_x");
}

int JsonFieldConfig::get_field_max_y() {
    return get_field_size_property("field_max_y");
}

std::vector<NpcFieldConfigData> JsonFieldConfig::get_field() {
    int max_x = get_field_max_x();
    int max_y = get_field_max_y();
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

        std::string name = npc.at("name").get<std::string>();
        std::string string_type = npc.at("type").get<std::string>();
        NpcType type = StringToNpcType.at(npc.at("type").get<std::string>());
        int x = npc.at("x").get<int>();
        int y = npc.at("y").get<int>();

        if (StringToNpcType.find(string_type) == StringToNpcType.end()) {
            std::string message =
                fmt::format("Invalid type for npc in config: (name: {}, "
                            "type: {}, x: {}, y: {})",
                            name, string_type, x, y);
            throw std::runtime_error(message);
        }

        if (x < 0 || x > max_x) {
            std::string message = fmt::format(
                "x cooordinate out of field for npc in config: (name: {}, "
                "type: {}, x: {}, y: {}), max_x is {}",
                name, string_type, x, y, max_x);
            throw std::runtime_error(message);
        }

        if (y < 0 || y > max_y) {
            std::string message = fmt::format(
                "y cooordinate out of field for npc in config: (name: {}, "
                "type: {}, x: {}, y: {}), max_y is {}",
                name, string_type, x, y, max_y);
            throw std::runtime_error(message);
        }

        npcs_data.push_back({name, type, x, y});
    }
    return npcs_data;
}

int JsonFieldConfig::get_field_size_property(const std::string &property) {
    if (!field_config.contains(property) ||
        !field_config[property].is_number()) {
        throw std::runtime_error("Not found in configuration or not "
                                 "integer in configuration: 'field_max_x'");
    }
    return field_config.at(property).get<int>();
}

// FieldConfigHandler

ptr<FieldConfig>
FieldConfigHandler::create_config(const std::string &file_path) {
    if (file_path_has_extension(file_path, ".json")) {
        return JsonFieldConfig::create(file_path);
    } else {
        throw std::runtime_error("Invalid config path!");
    }
}

bool FieldConfigHandler::file_path_has_extension(const std::string &file_path,
                                                 const std::string &extension) {
    std::filesystem::path path(file_path);
    return path.extension() == extension;
}