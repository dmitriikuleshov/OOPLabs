#pragma once
#include "config.hpp"
#include "dragon.hpp"
#include "frog.hpp"
#include "knight.hpp"
#include "npc.hpp"
#include "observer.hpp"

class NpcFactory : public std::enable_shared_from_this<NpcFactory> {
  protected:
    std::string npc_type_name;

    void set_npc_type_name(const std::string &type_name) {
        npc_type_name = type_name;
    }

    virtual void set_properties(std::shared_ptr<NPC> &npc);

  public:
    virtual std::shared_ptr<NPC> create_npc(const std::string &name, int x,
                                            int y) = 0;
};

class NpcFactoryWithConfig : public NpcFactory {
  public:
    NpcFactoryWithConfig(std::shared_ptr<INpcConfig> &conf) { config = conf; }

  protected:
    std::shared_ptr<INpcConfig> config;
    void set_properties(std::shared_ptr<NPC> &npc) {
        npc->set_move_distance(config->get_move_distance(npc_type_name));
        npc->set_kill_distance(config->get_kill_distance(npc_type_name));
        npc->set_enemies(config->get_enemies(npc_type_name));
    }
};

class KnightFactory final : public NpcFactoryWithConfig {
  public:
    std::shared_ptr<NPC> create_npc(const std::string &name, int x,
                                    int y) override {
        set_npc_type_name("Knight");
        std::shared_ptr<NPC> npc =
            std::static_pointer_cast<NPC>(std::make_shared<Knight>(name, x, y));
        set_properties(npc);
        return npc;
    }
};

class FrogFactory final : public NpcFactoryWithConfig {
  public:
    std::shared_ptr<NPC> create_npc(const std::string &name, int x,
                                    int y) override {
        set_npc_type_name("Frog");
        std::shared_ptr<NPC> npc =
            std::static_pointer_cast<NPC>(std::make_shared<Frog>(name, x, y));
        set_properties(npc);
        return npc;
    }
};

class DragonFactory final : public NpcFactoryWithConfig {
  public:
    std::shared_ptr<NPC> create_npc(const std::string &name, int x,
                                    int y) override {
        set_npc_type_name("Dragon");
        std::shared_ptr<NPC> npc =
            std::static_pointer_cast<NPC>(std::make_shared<Dragon>(name, x, y));
        set_properties(npc);
        return npc;
    }
};

class NpcGenerator {
  private:
    std::unordered_map<NpcType, std::shared_ptr<NpcFactory>> factories;
    void create_factories() {
        factories[NpcType::DragonType] = std::static_pointer_cast<NpcFactory>(
            std::make_shared<DragonFactory>());
        factories[NpcType::FrogType] = std::static_pointer_cast<NpcFactory>(
            std::make_shared<FrogFactory>());
        factories[NpcType::KnightType] = std::static_pointer_cast<NpcFactory>(
            std::make_shared<KnightFactory>());
    }

  public:
    NpcGenerator() { create_factories(); }
    std::shared_ptr<NPC> create_npc(const NpcType &type,
                                    const std::string &name, int x, int y) {
        return factories[type]->create_npc(name, x, y);
    }
};
