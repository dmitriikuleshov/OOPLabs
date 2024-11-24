#include "visitor.hpp"

// AttackerVisitorWithConfig
AttackerVisitorWithConfig::AttackerVisitorWithConfig(
    ptr<NpcPropertiesConfig> &conf, const std::string type_name) {
    attacker_type_name = type_name;
    config = conf;
    enemies = config->get_enemies(attacker_type_name);
}

// KnightAttackerVisitor
KnightAttackerVisitor::KnightAttackerVisitor(ptr<NpcPropertiesConfig> &conf)
    : AttackerVisitorWithConfig(conf, "Knight") {}

ptr<AttackerVisitor>
KnightAttackerVisitor::create(ptr<NpcPropertiesConfig> &conf) {
    return std::static_pointer_cast<AttackerVisitor>(
        std::make_shared<KnightAttackerVisitor>(conf));
}

void KnightAttackerVisitor::visit(const ptr<NPC> &npc) {
    if (enemies.find(npc->get_type()) != enemies.end()) {
        npc->must_die();
    }
}

// FrogAttackerVisitor
FrogAttackerVisitor::FrogAttackerVisitor(ptr<NpcPropertiesConfig> &conf)
    : AttackerVisitorWithConfig(conf, "Frog") {}

ptr<AttackerVisitor>
FrogAttackerVisitor::create(ptr<NpcPropertiesConfig> &conf) {
    return std::static_pointer_cast<AttackerVisitor>(
        std::make_shared<FrogAttackerVisitor>(conf));
}

void FrogAttackerVisitor::visit(const ptr<NPC> &npc) {
    if (enemies.find(npc->get_type()) != enemies.end()) {
        npc->must_die();
    }
}

// DragonAttackerVisitor
DragonAttackerVisitor::DragonAttackerVisitor(ptr<NpcPropertiesConfig> &conf)
    : AttackerVisitorWithConfig(conf, "Dragon") {}

ptr<AttackerVisitor>
DragonAttackerVisitor::create(ptr<NpcPropertiesConfig> &conf) {
    return std::static_pointer_cast<AttackerVisitor>(
        std::make_shared<DragonAttackerVisitor>(conf));
}

void DragonAttackerVisitor::visit(const ptr<NPC> &npc) {
    if (enemies.find(npc->get_type()) != enemies.end()) {
        npc->must_die();
    }
}