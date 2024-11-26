#ifndef FIELD_CONFIG_HPP
#define FIELD_CONFIG_HPP

#include "fmt/core.h"
#include "npc.hpp"
#include <nlohmann/json.hpp>

struct NpcFieldConfigData {
    std::string name;
    NpcType type;
    int x;
    int y;
};

class FieldConfig : std::enable_shared_from_this<FieldConfig> {
  public:
    virtual int get_field_max_x() = 0;
    virtual int get_field_max_y() = 0;
    virtual std::vector<NpcFieldConfigData> get_field() = 0;
};

class JsonFieldConfig : public FieldConfig {

  public:
    explicit JsonFieldConfig(const std::string &file_path);
    static ptr<FieldConfig> create(const std::string &file_path);
    JsonFieldConfig() = delete;

    int get_field_max_x() override;
    int get_field_max_y() override;

    std::vector<NpcFieldConfigData> get_field() override;

  private:
    using json = nlohmann::json;
    json field_config;
    int get_field_size_property(const std::string &property);
};

class FieldConfigHandler {
  public:
    static ptr<FieldConfig> create_config(const std::string &file_path);

  private:
    static bool file_path_has_extension(const std::string &file_path,
                                        const std::string &extension);
};

#endif // FIELD_CONFIG_HPP