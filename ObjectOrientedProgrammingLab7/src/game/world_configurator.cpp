#include "world_configurator.hpp"

WorldConfigurator::WorldConfigurator() {
    setup_npc_properties_config();
    setup_field_config();
    setup_attacker_visitors();
    setup_factories();
    setup_npc_generator();
    setup_field_size();
    generate_npcs();
}

ptr<WorldConfigurator> WorldConfigurator::create() {
    return std::make_shared<WorldConfigurator>();
}

ptr<AttackerVisitor>
WorldConfigurator::get_attacker_visitor(NpcType type) const {
    return attacker_visitors.at(type);
}
int WorldConfigurator::get_max_x() const { return field_max_x; }
int WorldConfigurator::get_max_y() const { return field_max_y; }

std::string WorldConfigurator::get_config_file_path(const std::string &env) {
    const char *path_raw = std::getenv(env.c_str());
    if (!path_raw) {
        throw std::runtime_error(
            "Could not get config file path using environment variable");
    }
    return std::string(path_raw);
}

void WorldConfigurator::setup_npc_properties_config() {
    npc_properties_config_file_path =
        get_config_file_path(npc_properties_config_file_path_env);
    npc_properties_config = NpcPropertiesConfigHandler::create_config(
        npc_properties_config_file_path);
    if (!npc_properties_config) {
        throw std::runtime_error(
            "Error while trying to get npc_properties_config");
    }
}

void WorldConfigurator::setup_npc_generator() {
    npc_generator = NpcGenerator::create(npc_factories);
    if (!npc_generator) {
        throw std::runtime_error("Error while trying to get npc_generator");
    }
}

void WorldConfigurator::setup_field_config() {
    field_config_file_path = get_config_file_path(field_config_file_path_env);
    field_config = FieldConfigHandler::create_config(field_config_file_path);
    if (!field_config) {
        throw std::runtime_error("Error while trying to get field_config");
    }
}

void WorldConfigurator::setup_attacker_visitors() {
    attacker_visitors[KnightType] =
        KnightAttackerVisitor::create(npc_properties_config);
    attacker_visitors[DragonType] =
        DragonAttackerVisitor::create(npc_properties_config);
    attacker_visitors[FrogType] =
        FrogAttackerVisitor::create(npc_properties_config);
}

void WorldConfigurator::setup_factories() {
    npc_factories[KnightType] = KnightFactory::create(npc_properties_config);
    npc_factories[DragonType] = DragonFactory::create(npc_properties_config);
    npc_factories[FrogType] = FrogFactory::create(npc_properties_config);
}

void WorldConfigurator::setup_field_size() {
    field_max_x = field_config->get_field_max_x();
    field_max_y = field_config->get_field_max_y();
}

void WorldConfigurator::generate_npcs() {
    npcs_field_data = field_config->get_field();
    for (const auto &data : npcs_field_data) {
        auto npc =
            npc_generator->create_npc(data.type, data.name, data.x, data.y);
        if (!npc) {
            throw std::runtime_error("Error creating npc with generator");
        }
        npcs.push_back(npc);
    }
}