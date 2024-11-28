#ifndef NPC_PROPERTIES_CONFIGS_HPP
#define NPC_PROPERTIES_CONFIGS_HPP

#include "npc_types.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_set>

class NpcPropertiesConfig : std::enable_shared_from_this<NpcPropertiesConfig> {
  public:
    virtual int get_move_distance(const std::string &npc_type_name) = 0;
    virtual int get_kill_distance(const std::string &npc_type_name) = 0;
    virtual std::unordered_set<NpcType>
    get_enemies(const std::string &npc_type_name) = 0;
};

class JsonNpcPropertiesConfig : public NpcPropertiesConfig {

  public:
    explicit JsonNpcPropertiesConfig(const std::string &file_path);
    static ptr<NpcPropertiesConfig> create(const std::string &file_path);
    JsonNpcPropertiesConfig() = delete;

    int get_move_distance(const std::string &npc_type_name) override;
    int get_kill_distance(const std::string &npc_type_name) override;

    std::unordered_set<NpcType>
    get_enemies(const std::string &npc_type_name) override;

  private:
    using json = nlohmann::json;
    json npc_config;
    void check_for_npc_in_config(const std::string &npc_type_name);
};

class NpcPropertiesConfigHandler {
  public:
    static ptr<NpcPropertiesConfig> create_config(const std::string &file_path);

  private:
    static bool file_path_has_extension(const std::string &file_path,
                                        const std::string &extension);
};

#endif // NPC_PROPERTIES_CONFIG_HPP