#pragma once
#include "dragon.hpp"
#include "frog.hpp"
#include "knight.hpp"
#include "npc.hpp"
#include "npc_properties_config.hpp"
#include "observer.hpp"

class NpcFactory;
class NpcFactoryWithConfig;
class KnightFactory;
class FrogFactory;
class DragonFactory;
class NpcGenerator;

class NpcFactory : public std::enable_shared_from_this<NpcFactory> {
  protected:
    virtual void set_properties(ptr<NPC> &npc) = 0;

  public:
    virtual ptr<NPC> create_npc(const std::string &name, int x, int y) = 0;
};

class NpcFactoryWithConfig : public NpcFactory {
  public:
    std::string npc_type_name;

    NpcFactoryWithConfig(ptr<NpcPropertiesConfig> &conf,
                         const std::string type_name) {
        config = conf;
        npc_type_name = type_name;
        // std::cout << "NpcFactoryWithConfig initialized with type: "
        //           << npc_type_name << std::endl;
    }

  protected:
    ptr<NpcPropertiesConfig> config;
    void set_properties(ptr<NPC> &npc) {
        npc->set_move_distance(config->get_move_distance(npc_type_name));
        npc->set_kill_distance(config->get_kill_distance(npc_type_name));
        npc->set_enemies(config->get_enemies(npc_type_name));
    }

  public:
    NpcFactoryWithConfig() = delete;
};

class KnightFactory final : public NpcFactoryWithConfig {
  public:
    KnightFactory(ptr<NpcPropertiesConfig> &conf)
        : NpcFactoryWithConfig(conf, "Knight") {}

    static ptr<NpcFactory> create(ptr<NpcPropertiesConfig> &conf) {
        return std::static_pointer_cast<NpcFactory>(
            std::make_shared<KnightFactory>(conf));
    }

    ptr<NPC> create_npc(const std::string &name, int x, int y) override {

        auto npc = Knight::create(name, x, y);
        set_properties(npc);
        return npc;
    }
};

class FrogFactory final : public NpcFactoryWithConfig {
  public:
    FrogFactory(ptr<NpcPropertiesConfig> &conf)
        : NpcFactoryWithConfig(conf, "Frog") {}

    static ptr<NpcFactory> create(ptr<NpcPropertiesConfig> &conf) {
        return std::static_pointer_cast<NpcFactory>(
            std::make_shared<FrogFactory>(conf));
    }

    ptr<NPC> create_npc(const std::string &name, int x, int y) override {
        auto npc = Frog::create(name, x, y);
        set_properties(npc);
        return npc;
    }
};

class DragonFactory final : public NpcFactoryWithConfig {
  public:
    DragonFactory(ptr<NpcPropertiesConfig> &conf)
        : NpcFactoryWithConfig(conf, "Dragon") {}

    static ptr<NpcFactory> create(ptr<NpcPropertiesConfig> &conf) {
        return std::static_pointer_cast<NpcFactory>(
            std::make_shared<DragonFactory>(conf));
    }

    ptr<NPC> create_npc(const std::string &name, int x, int y) override {
        auto npc = Dragon::create(name, x, y);
        set_properties(npc);
        return npc;
    }
};

class NpcGenerator {
  private:
    std::unordered_map<NpcType, ptr<NpcFactory>> factories;

  public:
    NpcGenerator(const std::unordered_map<NpcType, ptr<NpcFactory>> factories)
        : factories(factories) {}

    static ptr<NpcGenerator>
    create(std::unordered_map<NpcType, ptr<NpcFactory>> factories) {
        return std::make_shared<NpcGenerator>(factories);
    }
    ptr<NPC> create_npc(const NpcType &type, const std::string &name, int x,
                        int y) {
        return factories[type]->create_npc(name, x, y);
    }
};
