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

    virtual void set_properties(std::shared_ptr<NPC> &npc) = 0;

  public:
    virtual std::shared_ptr<NPC> create_npc(const std::string &name, int x,
                                            int y) = 0;
};

class NpcFactoryWithConfig : public NpcFactory {
  protected:
    NpcFactoryWithConfig(std::shared_ptr<INpcConfig> &conf) { config = conf; }
    std::shared_ptr<INpcConfig> config;
    void set_properties(std::shared_ptr<NPC> &npc) {
        npc->set_move_distance(config->get_move_distance(npc_type_name));
        npc->set_kill_distance(config->get_kill_distance(npc_type_name));
        npc->set_enemies(config->get_enemies(npc_type_name));
    }

  public:
    NpcFactoryWithConfig() = delete;
};

class KnightFactory final : public NpcFactoryWithConfig {
  protected:
    KnightFactory(std::shared_ptr<INpcConfig> &conf)
        : NpcFactoryWithConfig(conf) {};

  public:
    static std::shared_ptr<NpcFactory> create() {
        return std::static_pointer_cast<NpcFactory>(
            std::make_shared<KnightFactory>());
    }

    std::shared_ptr<NPC> create_npc(const std::string &name, int x,
                                    int y) override {
        set_npc_type_name("Knight");
        auto npc = Knight::create(name, x, y);
        set_properties(npc);
        return npc;
    }
};

class FrogFactory final : public NpcFactoryWithConfig {
  protected:
    FrogFactory(std::shared_ptr<INpcConfig> &conf)
        : NpcFactoryWithConfig(conf) {};

  public:
    static std::shared_ptr<NpcFactory> create() {
        return std::static_pointer_cast<NpcFactory>(
            std::make_shared<FrogFactory>());
    }

    std::shared_ptr<NPC> create_npc(const std::string &name, int x,
                                    int y) override {
        set_npc_type_name("Frog");
        auto npc = Frog::create(name, x, y);
        return npc;
    }
};

class DragonFactory final : public NpcFactoryWithConfig {
  protected:
    DragonFactory(std::shared_ptr<INpcConfig> &conf)
        : NpcFactoryWithConfig(conf) {};

  public:
    static std::shared_ptr<NpcFactory> create() {
        return std::static_pointer_cast<NpcFactory>(
            std::make_shared<DragonFactory>());
    }

    std::shared_ptr<NPC> create_npc(const std::string &name, int x,
                                    int y) override {
        set_npc_type_name("Dragon");
        auto npc = Dragon::create(name, x, y);
        return npc;
    }
};

class NpcGenerator {
  private:
    std::unordered_map<NpcType, std::shared_ptr<NpcFactory>> factories;
    void define_factories() {
        factories[NpcType::DragonType] = DragonFactory::create();
        factories[NpcType::FrogType] = FrogFactory::create();
        factories[NpcType::KnightType] = KnightFactory::create();
    }

  public:
    NpcGenerator() { define_factories(); }
    std::shared_ptr<NPC> create_npc(const NpcType &type,
                                    const std::string &name, int x, int y) {
        return factories[type]->create_npc(name, x, y);
    }
};
