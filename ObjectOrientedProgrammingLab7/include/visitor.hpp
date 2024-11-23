#pragma once
#include "config.hpp"
#include "npc.hpp"

class AttackerVisitor {
  public:
    virtual void visit(const std::shared_ptr<NPC> &npc) = 0;
};

class AttackerVisitorWithConfig : public AttackerVisitor {
  protected:
    std::shared_ptr<INpcConfig> config;
    std::unordered_set<NpcType> enemies;
    std::string attacker_type_name;

    void set_attacker_type_name(const std::string &name) {
        attacker_type_name = name;
    }

  public:
    AttackerVisitorWithConfig(std::shared_ptr<INpcConfig> &conf) {
        config = conf;
        enemies = config->get_enemies(attacker_type_name);
    }
};

class KnightAttackerVisitor : public AttackerVisitorWithConfig {
  public:
    KnightAttackerVisitor(std::shared_ptr<INpcConfig> &conf)
        : AttackerVisitorWithConfig(conf) {
        set_attacker_type_name("Knight");
    }

    void visit(const std::shared_ptr<NPC> &npc) override {
        if (enemies.find(npc->get_type()) != enemies.end()) {
            npc->must_die();
        }
    }
};

class FrogAttackerVisitor : public AttackerVisitorWithConfig {
  public:
    FrogAttackerVisitor(std::shared_ptr<INpcConfig> &conf)
        : AttackerVisitorWithConfig(conf) {
        set_attacker_type_name("Frog");
    }

    void visit(const std::shared_ptr<NPC> &npc) override {
        if (enemies.find(npc->get_type()) != enemies.end()) {
            npc->must_die();
        }
    }
};

class DragonAttackerVisitor : public AttackerVisitorWithConfig {
  public:
    DragonAttackerVisitor(std::shared_ptr<INpcConfig> &conf)
        : AttackerVisitorWithConfig(conf) {
        set_attacker_type_name("Dragon");
    }

    void visit(const std::shared_ptr<NPC> &npc) override {
        if (enemies.find(npc->get_type()) != enemies.end()) {
            npc->must_die();
        }
    }
};
