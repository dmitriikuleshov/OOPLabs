#include "factories.hpp"

NpcFactoryWithConfig::NpcFactoryWithConfig(ptr<NpcPropertiesConfig> &conf,
                                           const std::string type_name) {
    config = conf;
    npc_type_name = type_name;
}

void NpcFactoryWithConfig::set_properties(ptr<NPC> &npc) {
    npc->set_move_distance(config->get_move_distance(npc_type_name));
    npc->set_kill_distance(config->get_kill_distance(npc_type_name));
    npc->set_enemies(config->get_enemies(npc_type_name));
}

// KnightFactory

KnightFactory::KnightFactory(ptr<NpcPropertiesConfig> &conf)
    : NpcFactoryWithConfig(conf, "Knight") {}

ptr<NpcFactory> KnightFactory::create(ptr<NpcPropertiesConfig> &conf) {
    return std::static_pointer_cast<NpcFactory>(
        std::make_shared<KnightFactory>(conf));
}

ptr<NPC> KnightFactory::create_npc(const std::string &name, int x, int y) {
    auto npc = Knight::create(name, x, y);
    set_properties(npc);
    npc->subscribe(FileObserver::get());
    npc->subscribe(TextObserver::get());
    return npc;
}

// FrogFactory

FrogFactory::FrogFactory(ptr<NpcPropertiesConfig> &conf)
    : NpcFactoryWithConfig(conf, "Frog") {}

ptr<NpcFactory> FrogFactory::create(ptr<NpcPropertiesConfig> &conf) {
    return std::static_pointer_cast<NpcFactory>(
        std::make_shared<FrogFactory>(conf));
}

ptr<NPC> FrogFactory::create_npc(const std::string &name, int x, int y) {
    auto npc = Frog::create(name, x, y);
    set_properties(npc);
    npc->subscribe(FileObserver::get());
    npc->subscribe(TextObserver::get());
    return npc;
}

// DragonFactory

DragonFactory::DragonFactory(ptr<NpcPropertiesConfig> &conf)
    : NpcFactoryWithConfig(conf, "Dragon") {}

ptr<NpcFactory> DragonFactory::create(ptr<NpcPropertiesConfig> &conf) {
    return std::static_pointer_cast<NpcFactory>(
        std::make_shared<DragonFactory>(conf));
}

ptr<NPC> DragonFactory::create_npc(const std::string &name, int x, int y) {
    auto npc = Dragon::create(name, x, y);
    set_properties(npc);
    npc->subscribe(FileObserver::get());
    npc->subscribe(TextObserver::get());
    return npc;
}

// NpcGenerator

NpcGenerator::NpcGenerator(
    const std::unordered_map<NpcType, ptr<NpcFactory>> factories)
    : factories(factories) {}

ptr<NpcGenerator>
NpcGenerator::create(std::unordered_map<NpcType, ptr<NpcFactory>> factories) {
    return std::make_shared<NpcGenerator>(factories);
}

ptr<NPC> NpcGenerator::create_npc(const NpcType &type, const std::string &name,
                                  int x, int y) {
    return factories[type]->create_npc(name, x, y);
}