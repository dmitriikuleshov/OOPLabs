#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include "dragon.hpp"
#include "frog.hpp"
#include "knight.hpp"
#include "npc.hpp"
#include "npc_properties_config.hpp"

class NpcFactory : public std::enable_shared_from_this<NpcFactory> {
  public:
    virtual ptr<NPC> create_npc(const std::string &name, int x, int y) = 0;

  protected:
    virtual void set_properties(ptr<NPC> &npc) = 0;
};

class NpcFactoryWithConfig : public NpcFactory {
  public:
    std::string npc_type_name;

    NpcFactoryWithConfig(ptr<NpcPropertiesConfig> &conf,
                         const std::string type_name);
    NpcFactoryWithConfig() = delete;

  protected:
    ptr<NpcPropertiesConfig> config;
    void set_properties(ptr<NPC> &npc);
};

class KnightFactory final : public NpcFactoryWithConfig {
  public:
    KnightFactory(ptr<NpcPropertiesConfig> &conf);
    static ptr<NpcFactory> create(ptr<NpcPropertiesConfig> &conf);
    ptr<NPC> create_npc(const std::string &name, int x, int y) override;
};

class FrogFactory final : public NpcFactoryWithConfig {
  public:
    FrogFactory(ptr<NpcPropertiesConfig> &conf);
    static ptr<NpcFactory> create(ptr<NpcPropertiesConfig> &conf);
    ptr<NPC> create_npc(const std::string &name, int x, int y) override;
};

class DragonFactory final : public NpcFactoryWithConfig {
  public:
    DragonFactory(ptr<NpcPropertiesConfig> &conf);
    static ptr<NpcFactory> create(ptr<NpcPropertiesConfig> &conf);
    ptr<NPC> create_npc(const std::string &name, int x, int y) override;
};

class NpcGenerator {
  public:
    NpcGenerator(const std::unordered_map<NpcType, ptr<NpcFactory>> factories);

    static ptr<NpcGenerator>
    create(std::unordered_map<NpcType, ptr<NpcFactory>> factories);
    ptr<NPC> create_npc(const NpcType &type, const std::string &name, int x,
                        int y);

  private:
    std::unordered_map<NpcType, ptr<NpcFactory>> factories;
};

#endif // FACTORIES_HPP